#ifndef _GameObject_H
#define _GameObject_H

#include <memory>
#include <string>
#include <unordered_map>

#include "..\Events\MessageBus.hpp"

#include "..\Rendering\Transform.hpp"
#include "..\Rendering\Mesh.hpp"

#include "..\Util.hpp"


/**
 * TODO:
 * http://www.tomdalling.com/blog/modern-opengl/08-even-more-lighting-directional-lights-spotlights-multiple-lights/
 */
namespace Potion
{
	using GameObjectID = uint32_t;

	/**
	 * GameObject is the base class for anything that exists in the scene.
	 * It can either be empty, or have a mesh
	 * It has a position, rotation, scale.
	 */
	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject() {}

		void SetActive( bool active );
		bool IsActive() const;

		GameObjectID GetID() const;
		void SetID( GameObjectID id );

		Transform& GetTransform();

		// takes ownership
		void SetMesh( Mesh* mesh );
		Mesh* GetMesh();

		void SetLayer( int layer );
		int GetLayer() const;

	private:
		Transform m_transform;

		GameObjectID m_id;

		bool m_isActive;

		std::unique_ptr<Mesh> m_mesh;

		// Used to differentiate GOs per layer
		// For example used by the Camera to draw GOs selectively
		int m_layer;
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

#endif // _GameObject_H