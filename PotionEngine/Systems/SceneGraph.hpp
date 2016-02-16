#ifndef _SceneGraph_H
#define _SceneGraph_H

#include <vector>
#include <algorithm>
#include <stack>

#include "..\Events\MessageBus.hpp"

#include "..\World\GameObject.hpp"
#include "..\World\Light.hpp"
#include "..\World\Camera.hpp"

namespace Potion
{
	class GameObject;

	class SceneGraph : 	MessageReceiver< LightCreatedMessage, LightDestroyedMessage,
										 CameraCreatedMessage, CameraDestroyedMessage >
	{

	public:
		SceneGraph();
		virtual ~SceneGraph();

		void SetAmbientColor( const Color &color );

		// Should be [0 .. 1]. 
		void SetAmbientIntensity( float intensity );

		// Call to start drawing process
		virtual void DrawAll();

		/**
		 * Claims ownership of ptr. SceneGraph is responsible for managing the lifetime of the GO. 
		 * Gives the GameObject a new unique ID.
		 * Also attaches the GameObject to the root of the scene, if it doesn't have a root obj yet.
		 *
		 * @param GO The gameObject to add to this scene
		 */
		void AttachToScene( GameObject* GO );

		virtual Transform* GetRoot();

		virtual GameObject* FindGameObject( GameObjectID entity ) const;

		virtual void DestroyGameObject( const GameObjectID id );

		virtual void HandleMessage( const LightCreatedMessage& msg );
		virtual void HandleMessage( const LightDestroyedMessage& msg );

		virtual void HandleMessage( const CameraCreatedMessage& msg );
		virtual void HandleMessage( const CameraDestroyedMessage& msg );

	protected:
		virtual void GetRenderablesForCamera( Camera* cam, std::vector<GameObject*>& outObjects );

		virtual void RebuildMeshCache();

		Transform m_root;

		std::unordered_map<GameObjectID, GameObjectPtr> m_gameObjects;

		std::vector<Light*> m_lights;
		std::vector<Camera*> m_cameras;

		std::vector<Mesh*> m_meshCache;

		GameObjectID GetNextID();
		std::stack<GameObjectID> m_freeIDs;
		GameObjectID m_nextID;

		Color m_ambientColor;

		// [0 .. 1]
		float m_ambientIntensity;

	};
}

#endif // _SceneGraph_H