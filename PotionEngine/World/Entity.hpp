#ifndef _Entity_H
#define _Entity_H

#include <memory>

#include "..\Systems\EntitySystem.hpp"

#include "..\Rendering\Transform.hpp"
#include "..\Util.hpp"


/**
 * TODO:
 * Let MeshEntity register itself at RenderSystem.h
 * Have MeshEntity set light params for forward render mode
 * Have Camera.h only render MeshEntitys on its cullingLayers
 *
 * TODO.txt
 *
 * http://www.tomdalling.com/blog/modern-opengl/08-even-more-lighting-directional-lights-spotlights-multiple-lights/
 */
namespace Potion
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity() {}

		EntityID GetID() const;
		void SetID( EntityID id );

		Transform& GetTransform();

	private:
		EntityID m_id;

		Transform m_transform;
	};
}

#endif // _Entity_H