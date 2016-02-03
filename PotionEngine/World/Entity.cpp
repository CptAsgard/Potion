#include "Entity.hpp"

namespace Potion {
	EntityID Entity::GetID() const
	{
		return id;
	}

	void Entity::SetID( EntityID id )
	{
		this->id = id;
	}
}