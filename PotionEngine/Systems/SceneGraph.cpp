#include "SceneGraph.hpp"

namespace Potion
{
	SceneGraph::SceneGraph() : m_nextID( 0 )
	{
		Subscribe( Event, *this );

		this->m_freeIDs = std::stack<GameObjectID>();
		this->m_gameObjects = std::unordered_map<GameObjectID, GameObjectPtr>();
	}

	SceneGraph::~SceneGraph()
	{}

	/*
	 * The complexity of this function is: O( cameras * lights * objects )
	 * It's about as inefficient as it gets. However, the class is subclassable.
	 * Go write a BSPSceneGraph or an OctreeSceneGraph if you'd like.
	 */
	void SceneGraph::DrawAll()
	{
		RebuildMeshCache();

		SetAmbientColor( m_ambientColor );
		SetAmbientIntensity( m_ambientIntensity );

		// Loop over every camera to render
		for( Camera* camera : m_cameras )
		{
			std::vector<GameObject*> drawables;
			GetRenderablesForCamera( camera, drawables );

			for( const auto& go : drawables )
			{
				go->GetMesh()->GetMaterial()->GetShader()->SetUniform( std::string( "_WorldSpaceCameraPos" ), camera->GetTransform().GetPosition() );
				camera->Render( *go );
			}
		}
	}

	void SceneGraph::SetAmbientColor( const Color & color )
	{
		m_ambientColor = color;

		for( Mesh* meshPtr : m_meshCache )
		{
			meshPtr->GetMaterial()->GetShader()->SetUniform( "POT_AMBIENT_COLOR", m_ambientColor.AsRGB() );
		}
	}

	void SceneGraph::SetAmbientIntensity( float intensity )
	{
		m_ambientIntensity = intensity;

		for( Mesh* meshPtr : m_meshCache )
		{
			meshPtr->GetMaterial()->GetShader()->SetUniform( "POT_AMBIENT_INTENSITY", m_ambientIntensity );
		}
	}

	// TODO: Camera culling mask/GO layers
	// TODO: Material sorting 
	void SceneGraph::GetRenderablesForCamera( Camera * cam, std::vector<GameObject*>& outObjects )
	{
		for( const auto& kv : m_gameObjects )
		{
			auto* ptr = kv.second.get();

			if( ptr->GetMesh() != nullptr )
				outObjects.push_back( ptr );
		}
	}

	void SceneGraph::RebuildMeshCache()
	{
		m_meshCache.clear();

		// Build a cache of all meshes once every frame, after the update, so every function doesn't have to recreate it.
		// We recreate it every frame because it can change in the update loops.
		for( const auto& kv : m_gameObjects )
		{
			auto* ptr = kv.second.get();
			Mesh* meshPtr;
			if( ( meshPtr = ptr->GetMesh() ) != nullptr )
			{
				this->m_meshCache.push_back( meshPtr );
			}
		}
	}

	void SceneGraph::AttachToScene( GameObject * GO )
	{
		GameObjectID addedID = GetNextID();

		m_gameObjects.insert( std::pair<GameObjectID, GameObjectPtr>( addedID, GameObjectPtr( GO ) ) );
		GO->SetID( addedID );

		if( !GO->GetTransform().GetParent() )
			GO->GetTransform().SetParent( GetRoot() );

		printf( "   New GameObject added to scene. ID: %i\n", GO->GetID() );
	}

	Transform * SceneGraph::GetRoot()
	{
		return &m_root;
	}

	GameObject * SceneGraph::FindGameObject( GameObjectID entity ) const
	{
		return m_gameObjects.at( entity ).get();
	}

	void SceneGraph::DestroyGameObject( const GameObjectID id )
	{
		m_gameObjects.erase( id );
		m_freeIDs.push( id );
	}

	GameObjectID SceneGraph::GetNextID()
	{
		GameObjectID newID;

		if( m_freeIDs.size() != 0 )
		{
			newID = m_freeIDs.top();
			m_freeIDs.pop();
		}
		else
		{
			newID = m_nextID;
			m_nextID++;
		}

		return newID;
	}

	void SceneGraph::HandleMessage( const LightCreatedMessage & msg )
	{
		m_lights.push_back( msg.newObj );

		printf( "   Created a new light source!\n" );
	}

	void SceneGraph::HandleMessage( const LightDestroyedMessage & msg )
	{
		m_lights.erase( std::remove( m_lights.begin(), m_lights.end(), msg.newObj ), m_lights.end() );

		printf( "   Removed a light source!\n" );
	}

	void SceneGraph::HandleMessage( const CameraCreatedMessage & msg )
	{
		m_cameras.push_back( msg.newObj );

		printf( "   Created a new camera!\n" );
	}

	void SceneGraph::HandleMessage( const CameraDestroyedMessage & msg )
	{
		m_cameras.erase( std::remove( m_cameras.begin(), m_cameras.end(), msg.newObj ), m_cameras.end() );

		printf( "   Removed a camera!\n" );
	}
}