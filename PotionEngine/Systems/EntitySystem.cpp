#include "EntitySystem.hpp"

namespace Potion
{
	EntitySystem::EntitySystem() : nextID( 0 )
	{
		freeIDs = std::stack<EntityID>();
		entities = std::unordered_map<EntityID, EntityPtr>();
	}

	/**
	 * NOTE: This function claims ownership of the entity ptr
	 */
	Entity* EntitySystem::CreateEntity( Entity* entity )
	{
		EntityID addedID = GetNextID();

		entities.insert( std::pair<EntityID, EntityPtr>( addedID, EntityPtr( entity ) ) );
		entity->SetID( addedID );

		return entity;
	}

	Entity* EntitySystem::FindEntity( EntityID id ) const
	{
		return entities.at( id ).get();
	}

	void EntitySystem::DestroyEntity( const EntityID id )
	{
		entities.erase( id );
		freeIDs.push( id );
	}

	EntityID EntitySystem::GetNextID()
	{
		EntityID newID;

		if( freeIDs.size() != 0 ) {
			newID = freeIDs.top();
			freeIDs.pop();
		} else {
			newID = nextID;
			nextID++;
		}

		return newID;
	}

}