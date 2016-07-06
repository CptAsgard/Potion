#include "GameObject.hpp"

namespace Potion
{
	GameObject::GameObject() : transform( Transform( this ) )
	{}

	GameObject::~GameObject()
	{
		delete model;
	}

	void GameObject::SetActive( bool active )
	{
		this->isActive = active;
	}

	bool GameObject::IsActive() const
	{
		return isActive;
	}

	ID GameObject::GetID() const
	{
		return id;
	}

	void GameObject::SetID( ID id )
	{
		this->id = id;
	}

	Transform& GameObject::GetTransform()
	{
		return transform;
	}

	void GameObject::SetModel( Model * model )
	{
		this->model = model;
	}

	Model * GameObject::GetModel()
	{
		return model;
	}

	void GameObject::SetLayer( uint32_t layer )
	{
		this->layer = layer;
	}

	uint32_t GameObject::GetLayer() const
	{
		return layer;
	}
}