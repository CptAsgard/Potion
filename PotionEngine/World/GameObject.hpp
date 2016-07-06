#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include <memory>
#include <string>

#ifdef _DEBUG
#include <iostream>
#endif

#include "..\Rendering\Transform.hpp"
#include "..\Rendering\Model.hpp"

#include "..\Events\MessageBus.hpp"

#include "..\Utils\Utils.hpp"

namespace Potion
{
	class SceneManager;

	/**
	 * GameObject is the base class for anything that exists in the scene.
	 * It can either be empty, or have a mesh
	 * It has a position, rotation, scale.
	 */
	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Initialize( SceneManager *game ) { }
		virtual void Update( SceneManager *game, float deltaTime ) { }

		void SetActive( bool active );
		bool IsActive() const;

		ID GetID() const;
		void SetID( ID id );

		Transform& GetTransform();

		void SetModel( Model* model );
		Model* GetModel();

		void SetLayer( uint32_t layer );
		uint32_t GetLayer() const;

	private:
		Transform transform;

		ID id;

		bool isActive;

		Model* model;

		// Used to differentiate GOs per layer
		// For example used by the Camera to draw GOs selectively
		uint32_t layer;
	};

	using GameObjectPtr = std::unique_ptr<GameObject>;

	struct RegisterGameObjectMessage
	{
		RegisterGameObjectMessage( GameObject* ptr ) : newObj( ptr ) {}

		GameObject* newObj;
	};
	struct UnregisterGameObjectMessage
	{
		UnregisterGameObjectMessage( GameObject* ptr ) : newObj( ptr ) {}

		GameObject* newObj;
	};
}

#endif // _GAMEOBJECT_H