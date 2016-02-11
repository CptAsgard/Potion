#include "Entity.hpp"

namespace Potion
{
	Entity::Entity()
	{ 
		// send message for EntityManager
	}

	EntityID Entity::GetID() const
	{
		return m_id;
	}

	void Entity::SetID( EntityID id )
	{
		this->m_id = id;
	}

	Transform& Entity::GetTransform()
	{
		return m_transform;
	}
}