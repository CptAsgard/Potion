#pragma once
#ifndef _ENTITY_H
#define _ENTITY_H

#include "EntityManager.hpp"

namespace Potion {
	class Entity {
	public:
		EntityID GetID() const;
		void Entity::SetID( EntityID id );

	private:
		EntityID id;

	};
}
#endif // _ENTITY_H