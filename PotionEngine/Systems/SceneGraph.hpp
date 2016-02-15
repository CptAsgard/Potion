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

		void DrawAll();

		void SetAmbientLight( const Color &color );

		/**
		 * Claims ownership of ptr. SceneGraph is responsible for managing the lifetime. Also gives the GameObject an unique ID.
		 * Attaches the GameObject to the root of the scene.
		 *
		 * @param GO The gameObject to add to this scene
		 */
		void AttachToScene( GameObject* GO );

		virtual GameObject* GetRoot();

		virtual GameObject* FindGameObject( GameObjectID entity ) const;

		virtual void DestroyGameObject( const GameObjectID id );

		virtual void HandleMessage( const LightCreatedMessage& msg );
		virtual void HandleMessage( const LightDestroyedMessage& msg );

		virtual void HandleMessage( const CameraCreatedMessage& msg );
		virtual void HandleMessage( const CameraDestroyedMessage& msg );

	protected:
		GameObject* m_rootGameObject;

		std::unordered_map<GameObjectID, GameObjectPtr> m_gameObjects;

		std::vector<Light*> m_lights;
		std::vector<Camera*> m_cameras;

		GameObjectID GetNextID();
		std::stack<GameObjectID> m_freeIDs;
		GameObjectID m_nextID;

		Color m_ambientColor;

	};
}

#endif // _SceneGraph_H