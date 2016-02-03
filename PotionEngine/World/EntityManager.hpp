#pragma once
#ifndef _ENTITYMANAGER_H
#define _ENTITYMANAGER_H

#include <memory>
#include <unordered_map>
#include <stack>

class Entity;
using EntityID = uint32_t;

#include "Entity.hpp"

namespace Potion {

	using EntityPtr = std::shared_ptr<Entity>;
	using WeakEntityPtr = std::weak_ptr<Entity>;

	class EntityManager {
	public:
		EntityManager();

		WeakEntityPtr CreateEntity( std::unique_ptr<Entity> entity );

		WeakEntityPtr FindEntity( EntityID id ) const;

		void RemoveEntity( const EntityID id );

	private:
		EntityID GetNextID();

		std::unordered_map<EntityID, EntityPtr> entities;

		std::stack<EntityID> freeIDs;
		EntityID nextID;

	};
}
#endif // _ENTITYMANAGER_H