#include "SceneGraph.hpp"

namespace Potion
{
	SceneGraph::SceneGraph( SceneManager* game ) : game( game )
	{
		Subscribe( Event, *this );
	}
		
	/*
	 * The current rendering complexity is.. big. It doesn't care about view frustrum culling.
	 * However, the class is easily subclassable.
	 * Go write a BSPSceneGraph or an OctreeSceneGraph if you'd like :>
	 */
	void SceneGraph::DrawAll()
	{
		// TODO: Cache draw keys for efficiency
		BuildDrawBucket();

		Renderer* renderer = nullptr;
		RenderDataPayload* prevPayload = nullptr;

		for( auto& kv : this->drawBucket )
		{
			RenderDataPayload* payload = &kv.second;

			// If the material changed, we want a new renderer.
			if( prevPayload == nullptr || payload->material != prevPayload->material )
			{
				if( renderer )
				{
					renderer->End();
				}

				renderer = new Renderer( payload->material );
				renderer->Begin( *payload->camera->GetViewMatrix(), *payload->camera->GetProjectionMatrix() );
			}

			// If camera changed, end old and start new camera
			if( prevPayload == nullptr || payload->camera != prevPayload->camera )
			{
				if( prevPayload )
				{
					prevPayload->camera->EndDraw();
				}

				payload->camera->StartDraw();
			}

			renderer->Render( *payload );

			// If we just rendered the last key of the bucket, close the renderer
			if( &kv.second == &this->drawBucket.rbegin()->second )
			{
				payload->camera->EndDraw();
				renderer->End();
			}

			prevPayload = payload;
		}

		delete renderer;
	}

	void SceneGraph::UpdateGameObjects( SceneManager * game, float deltaTime )
	{
		// The matrix stack keeps track of the current combined local-to-world transform
		MatrixStack stack;

		Transform* currentNode = &this->root;

		Recurse( currentNode, stack, [this, game = game, deltaTime = deltaTime]( Transform* t )
		{
			this->UpdateNode( t, game, deltaTime );
		} );
	}

	// TODO: Set ambient color values
	void SceneGraph::SetAmbientColor( const Color & color )
	{
		this->ambientColor = color;

		//for( Mesh* meshPtr : m_meshCache )
		//{
		//	meshPtr->GetMaterial()->GetShader()->SetUniform( "POT_AMBIENT_COLOR", m_ambientColor.AsRGB() );
		//}
	}

	// TODO: Set ambient lighting values
	void SceneGraph::SetAmbientIntensity( float intensity )
	{
		this->ambientIntensity = intensity;

		//for( Mesh* meshPtr : m_meshCache )
		//{
		//	meshPtr->GetMaterial()->GetShader()->SetUniform( "POT_AMBIENT_INTENSITY", m_ambientIntensity );
		//}
	}

	/**
	 // TODO: Uniform buffer object
	 */
	template<typename T>
	inline void SceneGraph::SetLightUniform( Shader * shader, const char * propertyName, size_t lightIndex, const T & value )
	{
		std::ostringstream ss;
		ss << "_Lights[" << lightIndex << "]." << propertyName;

		shader->SetUniform( ss.str(), value );
	}

	GameObject* SceneGraph::CreateGameObject( const std::string& path )
	{
		GameObject* go = CreateGameObject();
		go->SetModel( new Model( path, &mat ) );

		return go;
	}

	GameObject * SceneGraph::CreateGameObject()
	{
		GameObject* go = new GameObject();
		AttachToScene( go );

		go->Initialize( game );

		return go;
	}

	void SceneGraph::AttachToScene( GameObject * GO )
	{
		ID addedID = uniqueID.GetNext();

		gameObjects.insert( std::pair<ID, GameObjectPtr>( addedID, GameObjectPtr( GO ) ) );

		// Give the GameObject an unique ID
		GO->SetID( addedID );

		// and set its parent to the scene root
		if( !GO->GetTransform().GetParent() )
			GO->GetTransform().SetParent( GetRoot() );

		GO->Initialize( game );

		printf( "   New GameObject added to scene. ID: %i\n", GO->GetID() );
	}

	Transform * SceneGraph::GetRoot()
	{
		return &root;
	}

	GameObject * SceneGraph::FindGameObject( ID goID ) const
	{
		if( gameObjects.find( goID ) != gameObjects.end() )
			return gameObjects.at( goID ).get();
		else
			return nullptr;
	}

	void SceneGraph::DestroyGameObject( GameObject * obj )
	{
		if( obj != nullptr )
			DestroyGameObject( obj->GetID() );
	}

	void SceneGraph::DestroyGameObject( const ID id )
	{
		if( gameObjects.find( id ) != gameObjects.end() )
		{
			gameObjects.erase( id );
			uniqueID.Free( id );
		}
	}

	/**
	 * 31                                                          0
	 * [ Camera ID ][ Translucency ][   Material ID   ][  -(TBD)-  ]
	 *     8 bits       2 bits           16 bits          6 bits
	 *
	 * Camera ID    - There could be multiple cameras for e.g. multiplayer splitscreen, for mirrors or portals in the scene, etc.
	 * Translucency - We sort {opaque}, {normal translucent}, {additive translucent}, and {subtractive translucent}
					  geometry into separate groups.
	 * Material ID  - We want to sort by material to minimize state settings (textures, shaders, constants).
	 *
	 * Concept partially by Christer Ericson (http://realtimecollisiondetection.net/blog/?p=86)
	 */
	DrawKey SceneGraph::GenerateDrawKey( Camera * cam, Material * mat ) const
	{
		DrawKey key = 0;

		uint32_t writeMaskCameraID = CreateWriteMask( 8, 25 );
		uint32_t writeMaskTranslucency = CreateWriteMask( 2, 23 );
		uint32_t writeMaskMaterialID = CreateWriteMask( 16, 7 );

		uint8_t cameraID = cam->GetCameraID();
		key = (key & writeMaskCameraID) | (cameraID << 24);

		uint8_t translucency = static_cast<uint32_t>(mat->GetTranslucency());
		key = (key & writeMaskTranslucency) | (translucency << 22);

		uint16_t materialID = mat->GetID();
		key = (key & writeMaskMaterialID) | (materialID << 6);

		return key;
	}

	uint32_t SceneGraph::CreateReadMask( uint fieldLength, uint fieldIndex ) const
	{
		return ((1 << fieldLength) - 1) << (fieldIndex - 1);
	}

	uint32_t SceneGraph::CreateWriteMask( uint fieldLength, uint fieldIndex ) const
	{
		return ~CreateReadMask( fieldLength, fieldIndex );
	}

	void SceneGraph::BuildDrawBucket()
	{
		drawBucket.clear();

		for( const auto& cam : cameras )
		{
			// The matrix stack keeps track of the current combined local-to-world transform
			MatrixStack stack;
			
			Transform* currentNode = &this->root;

			Recurse( currentNode, stack, [this, &cam = cam, &stack = stack]( Transform* t )
			{
				this->AddNodeToDrawBucket( t, cam, &stack.GetAll() );
			} );
		}
	}

	void SceneGraph::Recurse( Transform* node, MatrixStack& stack, std::function<void( Transform* )> const& routine )
	{
		stack.Push( *node->GetLocalToWorldMatrix() );

		routine( node );

		if( node->GetChildCount() > 0 )
		{
			for( int i = 0; i < node->GetChildCount(); i++ )
			{
				Recurse( node->GetChild( i ), stack, routine );
			}
		}

		stack.Pop();
	}

	void SceneGraph::UpdateNode( Transform * node, SceneManager* game, float deltaTime )
	{
		if( node->GetGameObject() != nullptr )
		{
			node->GetGameObject()->Update( game, deltaTime );
		}
	}

	void SceneGraph::AddNodeToDrawBucket( Transform * node, Camera * cam, Matrix * worldMat )
	{
		Model* model = nullptr;

		// We only want to create draw keys for objects that have a model
		if( node->GetGameObject() != nullptr &&
			!cam->IsCulled( node->GetGameObject()->GetLayer() ) &&
			( model = node->GetGameObject()->GetModel() ) != nullptr )
		{
			// Models can have submeshes.
			// For every mesh in the model
			for( size_t i = 0; i < model->m_meshes.size(); i++ )
			{
				DrawKey key = GenerateDrawKey( cam, model->m_materials[ i ] );

				// We create a new data payload with all the necessary info
				// for the Renderer to take care of.
				RenderDataPayload payload = RenderDataPayload(
					model->m_meshes[ i ],
					model->m_materials[ i ],
					*worldMat, // world transform matrix
					cam );

				this->drawBucket.insert( std::pair<DrawKey, RenderDataPayload>( key, payload ) );
			}
		}
	}

	void SceneGraph::HandleMessage( const LightCreatedMessage & msg )
	{
		lights.push_back( msg.newObj );

		printf( "   Created a new light source!\n" );
	}

	void SceneGraph::HandleMessage( const LightDestroyedMessage & msg )
	{
		lights.erase( std::remove( lights.begin(), lights.end(), msg.newObj ), lights.end() );

		printf( "   Removed a light source!\n" );
	}

	void SceneGraph::HandleMessage( const CameraCreatedMessage & msg )
	{
		cameras.push_back( msg.newObj );

		printf( "   Created a new camera!\n" );
	}

	void SceneGraph::HandleMessage( const CameraDestroyedMessage & msg )
	{
		cameras.erase( std::remove( cameras.begin(), cameras.end(), msg.newObj ), cameras.end() );

		printf( "   Removed a camera!\n" );
	}
}