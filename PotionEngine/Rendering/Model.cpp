#include "Model.hpp"

using namespace Potion;

Model::Model( const std::string & path, Material* tempMat ) : tempMat( tempMat )
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile( path, aiProcess_Triangulate | aiProcess_OptimizeMeshes | aiProcess_FlipUVs );

	if( !scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode )
	{
		printf( "ERROR::ASSIMP:: %s\n", importer.GetErrorString() );
		return;
	}

	this->directory = path.substr( 0, path.find_last_of( '/' ) );

	this->ProcessAssimpNode( scene->mRootNode, scene );
}

Potion::Model::~Model()
{
	for( auto it = m_meshes.begin(); it != m_meshes.end(); ++it )
	{
		delete (*it);
	}
	m_meshes.clear();

	for( auto it = m_materials.begin(); it != m_materials.end(); ++it )
	{
		delete (*it);
	}
	m_materials.clear();
}

void Model::ProcessAssimpNode( aiNode * node, const aiScene * scene )
{
	for( GLuint i = 0; i < node->mNumMeshes; i++ )
	{
		aiMesh* mesh = scene->mMeshes[ node->mMeshes[ i ] ];
		this->ProcessAssimpMesh( mesh, scene );
	}

	for( GLuint i = 0; i < node->mNumChildren; i++ )
	{
		ProcessAssimpNode( node->mChildren[ i ], scene );
	}
}

void Model::ProcessAssimpMesh( aiMesh * mesh, const aiScene * scene )
{
	std::vector<VertexFormat> vertices;
	std::vector<GLushort> indices;

	// Vertices
	for( GLuint i = 0; i < mesh->mNumVertices; i++ )
	{
		VertexFormat vertex;

		Vector3  vector;
		vector.X = mesh->mVertices[ i ].x;
		vector.Y = mesh->mVertices[ i ].y;
		vector.Z = mesh->mVertices[ i ].z;
		vertex.Position = vector;

		vector.X = mesh->mNormals[ i ].x;
		vector.Y = mesh->mNormals[ i ].y;
		vector.Z = mesh->mNormals[ i ].z;
		vertex.Normal = vector;

		if( mesh->mTextureCoords[ 0 ] )
		{
			Vector2 vector;
			vector.X = mesh->mTextureCoords[ 0 ][ i ].x;
			vector.Y = mesh->mTextureCoords[ 0 ][ i ].y;
			vertex.Texture = vector;
		}
		else
			vertex.Texture = Vector2::Zero;

		vertices.push_back( vertex );
	}

	// Indices
	for( GLuint i = 0; i < mesh->mNumFaces; i++ )
	{
		aiFace* face = &mesh->mFaces[ i ];
		for( GLuint j = 0; j < face->mNumIndices; j++ )
		{
			indices.push_back( face->mIndices[ j ] );
		}
	}

	// Materials
	if( mesh->mMaterialIndex >= 0 )
	{
		ProcessAssimpMaterial( scene->mMaterials[ mesh->mMaterialIndex ] );
	}

	m_meshes.push_back( new Mesh() );
	m_meshes.back()->SetVertices( std::move( vertices ) );
	m_meshes.back()->SetIndices( std::move( indices ) );
	m_meshes.back()->Apply();
}

void Model::ProcessAssimpMaterial( aiMaterial * mat )
{
	std::string matName;
	{
		aiString aiString_matName;
		if( mat->Get( AI_MATKEY_NAME, aiString_matName ) != AI_SUCCESS )
		{
			int i = 0;
		}
		matName = aiString_matName.C_Str();
	}

	// TODO: Material* newMat = Material::FindOrCreate( matName );
	Material* newMat = nullptr;

	// TODO: Temporary. Material sharing should be through ResourceManager
	for( Material* m : m_materials )
	{
		if( m->GetName() == matName )
			newMat = m;
	}

	if( newMat == nullptr )
	{
		newMat = new Material();
		newMat->SetName( matName );

		newMat->SetTranslucency( TranslucencyType::TT_OPAQUE );

		for( GLuint i = 0; i < mat->GetTextureCount( aiTextureType_DIFFUSE ); i++ )
		{
			aiString str;
			mat->GetTexture( aiTextureType_DIFFUSE, i, &str );

			newMat->SetMainTexture( new Texture( directory + std::string( "/" ) + std::string( str.C_Str() ) ) );
		}
	}

	m_materials.push_back( newMat );
}