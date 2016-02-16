#include "GameObject.hpp"

namespace Potion
{
	GameObject::GameObject()
	{ }

	void GameObject::SetActive( bool active )
	{
		this->m_isActive = active;
	}

	bool GameObject::IsActive() const
	{
		return m_isActive;
	}

	GameObjectID GameObject::GetID() const
	{
		return m_id;
	}

	void GameObject::SetID( GameObjectID id )
	{
		this->m_id = id;
	}

	Transform& GameObject::GetTransform()
	{
		return m_transform;
	}

	void GameObject::SetMesh( Mesh * mesh )
	{
		this->m_mesh.reset( mesh );
	}

	Mesh * GameObject::GetMesh()
	{
		return m_mesh.get();
	}

	void GameObject::SetLayer( int layer )
	{
		this->m_layer = layer;
	}

	int GameObject::GetLayer() const
	{
		return m_layer;
	}
}