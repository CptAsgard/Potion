#include "EntityManager.hpp"

namespace Potion {
	EntityManager::EntityManager() : nextID( 0 )
	{
		freeIDs = std::stack<EntityID>();
		entities = std::unordered_map<EntityID, EntityPtr>();
	}

	/**
	 * NOTE: This function claims ownership of the entity ptr
	 */
	WeakEntityPtr EntityManager::CreateEntity( std::unique_ptr<Entity> entity )
	{
		EntityPtr added{ std::move( entity ) }; // Claim ptr ownership of entity
		EntityID addedID = GetNextID();

		entities.insert( std::pair<EntityID, EntityPtr>( addedID, added ) );
		added->SetID( addedID );

		return added;
	}

	WeakEntityPtr EntityManager::FindEntity( EntityID id ) const
	{
		return entities.at( id );
	}

	void EntityManager::RemoveEntity( const EntityID id )
	{
		freeIDs.push( id );
	}

	EntityID EntityManager::GetNextID()
	{
		EntityID newID;

		if( freeIDs.size() != 0 )
		{
			newID = freeIDs.top();
			freeIDs.pop();
		}
		else
		{
			newID = nextID;
			nextID++;
		}

		return newID;
	}
}