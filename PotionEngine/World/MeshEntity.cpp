#include "MeshEntity.hpp"

namespace Potion
{
	MeshEntity* MeshEntity::CreatePrimitive( PrimitiveType type )
	{
		MeshEntity* go = new MeshEntity();
		go->SetMesh( new Mesh() );

		Vertex verts[] = {
			Vertex( Vector3( -1.0f, -1.0f, 1.0f ), Vector2( 0.0f, 1.0f ), Vector3( 0.f, 0.f, 1.0f ) ),
			Vertex( Vector3( 1.0f, -1.0f, 1.0f ), Vector2( 1.0f, 1.0f ), Vector3( 0.f, 0.f, 1.0f ) ),
			Vertex( Vector3( 1.0f, 1.0f, 1.0f ), Vector2( 1.0f, 0.0f ), Vector3( 0.f, 0.f, 1.0f ) ),
			Vertex( Vector3( -1.0f, 1.0f, 1.0f ), Vector2( 0.0f, 0.0f ), Vector3( 0.f, 0.f, 1.0f ) ),

			Vertex( Vector3( 1.0f, -1.0f, 1.0f ), Vector2( 0.0f, 1.0f ), Vector3( 1.0f, 0.0f, 0.0f ) ),
			Vertex( Vector3( 1.0f, -1.0f, -1.0f ), Vector2( 1.0f, 1.0f ), Vector3( 1.0f, 0.0f, 0.0f ) ),
			Vertex( Vector3( 1.0f, 1.0f, -1.0f ), Vector2( 1.0f, 0.0f ), Vector3( 1.0f, 0.0f, 0.0f ) ),
			Vertex( Vector3( 1.0f, 1.0f, 1.0f ), Vector2( 0.0f, 0.0f ), Vector3( 1.0f, 0.0f, 0.0f ) ),

			Vertex( Vector3( 1.0f, -1.0f, -1.0f ), Vector2( 0.0f, 1.0f ), Vector3( 0.0f, 0.0f, -1.0f ) ),
			Vertex( Vector3( -1.0f, -1.0f, -1.0f ), Vector2( 1.0f, 1.0f ), Vector3( 0.0f, 0.0f, -1.0f ) ),
			Vertex( Vector3( -1.0f, 1.0f, -1.0f ), Vector2( 1.0f, 0.0f ), Vector3( 0.0f, 0.0f, -1.0f ) ),
			Vertex( Vector3( 1.0f, 1.0f, -1.0f ), Vector2( 0.0f, 0.0f ), Vector3( 0.0f, 0.0f, -1.0f ) ),

			Vertex( Vector3( -1.0f, -1.0f, -1.0f ), Vector2( 0.0f, 1.0f ), Vector3( -1.0f, 0.0f, 0.0f ) ),
			Vertex( Vector3( -1.0f, -1.0f, 1.0f ), Vector2( 1.0f, 1.0f ), Vector3( -1.0f, 0.0f, 0.0f ) ),
			Vertex( Vector3( -1.0f, 1.0f, 1.0f ), Vector2( 1.0f, 0.0f ), Vector3( -1.0f, 0.0f, 0.0f ) ),
			Vertex( Vector3( -1.0f, 1.0f, -1.0f ), Vector2( 0.0f, 0.0f ), Vector3( -1.0f, 0.0f, 0.0f ) ),

			Vertex( Vector3( -1.0f, 1.0f, 1.0f ), Vector2( 0.0f, 1.0f ), Vector3( 0.0f, 1.0f, 0.0f ) ),
			Vertex( Vector3( 1.0f, 1.0f, 1.0f ), Vector2( 1.0f, 1.0f ), Vector3( 0.0f, 1.0f, 0.0f ) ),
			Vertex( Vector3( 1.0f, 1.0f, -1.0f ), Vector2( 1.0f, 0.0f ), Vector3( 0.0f, 1.0f, 0.0f ) ),
			Vertex( Vector3( -1.0f, 1.0f, -1.0f ), Vector2( 0.0f, 0.0f ), Vector3( 0.0f, 1.0f, 0.0f ) ),

			Vertex( Vector3( 1.0f, -1.0f, 1.0f ), Vector2( 0.0f, 1.0f ), Vector3( 0.0f, -1.0f, 0.0f ) ),
			Vertex( Vector3( -1.0f, -1.0f, 1.0f ), Vector2( 1.0f, 1.0f ), Vector3( 0.0f, -1.0f, 0.0f ) ),
			Vertex( Vector3( -1.0f, -1.0f, -1.0f ), Vector2( 1.0f, 0.0f ), Vector3( 0.0f, -1.0f, 0.0f ) ),
			Vertex( Vector3( 1.0f, -1.0f, -1.0f ), Vector2( 0.0f, 0.0f ), Vector3( 0.0f, -1.0f, 0.0f ) )
		};

		GLuint indices[] = {
			// Font face
			0, 1, 2, 2, 3, 0,
			// Right face
			7, 6, 5, 5, 4, 7,
			// Back face
			11, 10, 9, 9, 8, 11,
			// Left face
			15, 14, 13, 13, 12, 15,
			// Top Face	
			19, 18, 17, 17, 16, 19,
			// Bottom Face
			23, 22, 21, 21, 20, 23
		};

		go->GetMesh()->ApplyVertices( verts, 24 );
		go->GetMesh()->ApplyIndices( indices, 36 );

		return go;
	}

	void MeshEntity::Render( Camera* cam )
	{
		GetMesh()->GetMaterial()->GetShader()->SetUniform( std::string( "_MeshEntity2World" ), GetTransform().GetLocalToWorldMatrix() );
		GetMesh()->GetMaterial()->GetShader()->SetUniform( std::string( "_Normal2World" ), GetTransform().GetLocalToWorldMatrix().Inverted().Mirror() );

		// foreach attached mesh
		GetMesh()->GLDraw( cam->TransformModelMatrixToMVP( GetTransform().GetLocalToWorldMatrix() ) );
	}

	void MeshEntity::SetMesh( Mesh * mesh )
	{
		this->m_mesh = *mesh;
	}

	Mesh * MeshEntity::GetMesh()
	{
		return &m_mesh;
	}

	void MeshEntity::SetLayer( int layer )
	{
		// layer 0 .. 31
		POT_ASSERT( layer <= 31 );

		this->m_layer = layer;
	}

	int MeshEntity::GetLayer() const
	{
		return m_layer;
	}
}