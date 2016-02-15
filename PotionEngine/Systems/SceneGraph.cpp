#include "SceneGraph.hpp"

namespace Potion
{
	SceneGraph::SceneGraph() : m_nextID( 0 )
	{
		Subscribe( Event, *this );

		this->m_rootGameObject = new GameObject();

		this->m_freeIDs = std::stack<GameObjectID>();
		this->m_gameObjects = std::unordered_map<GameObjectID, GameObjectPtr>();
	}

	SceneGraph::~SceneGraph()
	{ }

	// TODO: Take into account parent transforms
	void SceneGraph::DrawAll()
	{
		std::vector<Mesh*> drawables;

		for( const auto& kv : m_gameObjects )
		{
			auto* ptr = kv.second.get();
			
			if( ptr->GetMesh() != nullptr )
				m_cameras.at( 0 )->Render( *ptr );
		}
	}

	// TODO: Set ambient light shader uniform for all materials
	void SceneGraph::SetAmbientLight( const Color & color )
	{
		for( const auto& kv : m_gameObjects )
		{
			auto* ptr = kv.second.get();
			Mesh* meshPtr;

			if( ( meshPtr = ptr->GetMesh() ) != nullptr )
				meshPtr->GetMaterial()->GetShader()->SetUniform( std::string( "_WorldSpaceCameraPos" ), m_cameras.at( 0 )->GetTransform().GetPosition() );
		}

		m_ambientColor = color;
	}

	void SceneGraph::AttachToScene( GameObject * GO )
	{
		GameObjectID addedID = GetNextID();

		m_gameObjects.insert( std::pair<GameObjectID, GameObjectPtr>( addedID, GameObjectPtr( GO ) ) );
		GO->SetID( addedID );

		GetRoot()->AddChild( GO );

		printf( "New GameObject added to scene. ID: %i\n", GO->GetID() );
	}

	GameObject * SceneGraph::GetRoot()
	{
		return m_rootGameObject;
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

		if( m_freeIDs.size() != 0 ) {
			newID = m_freeIDs.top();
			m_freeIDs.pop();
		} else {
			newID = m_nextID;
			m_nextID++;
		}

		return newID;
	}

	void SceneGraph::HandleMessage(const LightCreatedMessage & msg)
	{
		m_lights.push_back( msg.newObj );

		printf( "Created a new light source!\n" );
	}

	void SceneGraph::HandleMessage(const LightDestroyedMessage & msg)
	{
		m_lights.erase( std::remove( m_lights.begin(), m_lights.end(), msg.newObj ), m_lights.end() );

		printf( "Removed a light source!\n" );
	}

	void SceneGraph::HandleMessage(const CameraCreatedMessage & msg)
	{
		m_cameras.push_back( msg.newObj );

		printf( "Created a new camera!\n" );
	}

	void SceneGraph::HandleMessage(const CameraDestroyedMessage & msg)
	{
		m_cameras.erase( std::remove( m_cameras.begin(), m_cameras.end(), msg.newObj ), m_cameras.end() );
		
		printf( "Removed a camera!\n" );
	}
}