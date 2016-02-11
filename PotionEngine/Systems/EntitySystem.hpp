#pragma once
#ifndef _ENTITYSYSTEM_H
#define _ENTITYSYSTEM_H

#include <memory>
#include <unordered_map>
#include <stack>

class Entity;
using EntityID = uint32_t;

#include "..\World\Entity.hpp"

namespace Potion
{
	using EntityPtr = std::unique_ptr<Entity>;

	class EntitySystem
	{
	public:
		EntitySystem();

		Entity* CreateEntity( Entity* entity );

		Entity* FindEntity( EntityID id ) const;

		void DestroyEntity( const EntityID id );

	private:
		EntityID GetNextID();

		std::unordered_map<EntityID, EntityPtr> entities;

		std::stack<EntityID> freeIDs;
		EntityID nextID;


	};
}
#endif // _ENTITYSYSTEM_H 