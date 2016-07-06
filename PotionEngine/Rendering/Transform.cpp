#include "Transform.hpp"
#include "..\Utils\Defines.hpp"

#include <math.h>
#include <cfloat>

namespace Potion
{
	Transform::Transform( GameObject* gameObject )
	{
		SetPosition( Vector3( 0, 0, 0 ) );
		SetRotation( Vector3( 0, 0, 0 ) );
		SetScale( Vector3( 1, 1, 1 ) );

		this->gameObject = gameObject;
	}

	void Transform::Translate( Vector3 & pos )
	{
		pos = GetRotationMatrix().TransformDirectionVector( pos );

		this->position += pos;
	}

	void Transform::Rotate( Vector3 & rot )
	{
		this->rotation += rot;
	}

	void Transform::SetPosition( Vector3 & pos )
	{
		this->position = pos;
	}

	Vector3 Transform::GetPosition() const
	{
		return this->position;
	}

	//Vector3 Transform::GetPosition() const
	//{
	//	if( m_parent )
	//		return m_parent->GetPosition() + m_position;
	//	else
	//		return m_position;
	//}

	void Transform::SetRotation( const Vector3 & rot )
	{
		this->rotation = rot;
	}

	Vector3 Transform::GetRotation() const
	{
		return this->rotation;
	}

	//Vector3 Transform::GetRotation() const
	//{
	//	if( m_parent )
	//		return m_parent->GetRotation() + m_rotation;
	//	else
	//		return m_rotation;
	//}

	void Transform::SetScale( Vector3 & scale )
	{
		this->scale = scale;
	}

	Vector3 Transform::GetScale() const
	{
		return this->scale;
	}

	//Vector3 Transform::GetScale() const
	//{
	//	if( m_parent )
	//		return m_parent->GetScale() + m_scale;
	//	else
	//		return m_scale;
	//}

	void Transform::LookAt( Vector3 target )
	{
		Vector3 lookDir = ( target - GetPosition() ).Normalized();

		float lookLengthOnXZ = sqrtf( lookDir.Z*lookDir.Z + lookDir.X*lookDir.X );
		float m_rotationX = -RadToDeg( atan2f( lookDir.Y, lookLengthOnXZ ) );
		float m_rotationY = RadToDeg( atan2f( lookDir.X, lookDir.Z ) );

		SetRotation( Vector3( m_rotationX, m_rotationY, GetRotation().Z ) );

		RecalculateMatrix();
	}

	Matrix* Transform::GetLocalToWorldMatrix()
	{
		RecalculateMatrix();
		return &matrix;
	}

	Vector3 Transform::GetForward()
	{
		return GetRotationMatrix().TransformDirectionVector( Vector3( 0, 0, 1 ) );
	}

	void Transform::RecalculateMatrix()
	{
		matrix = Matrix::CreateTranslation( GetPosition() ) * GetRotationMatrix() * Matrix::CreateScale( GetScale() );
	}

	Matrix Transform::GetRotationMatrix()
	{
		Vector3 worldRotation = GetRotation();
		return ( Matrix::CreateRotateZ( worldRotation.Z ) * Matrix::CreateRotateY( worldRotation.Y ) * Matrix::CreateRotateX( worldRotation.X ) );
	}

	void Transform::AddChild( Transform * obj )
	{
		children.push_back( obj );
	}

	void Transform::RemoveChild( Transform * obj )
	{
		if( children.size() < 1 )
			return;

		auto it = std::remove( children.begin(), children.end(), obj );

		if( it != children.end() )
			children.erase( it, children.end() );
	}

	Transform * Transform::GetChild( int index )
	{
		return children[ index ];
	}

	unsigned int Transform::GetChildCount() const
	{
		return children.size();
	}

	void Transform::SetParent( Transform * newParent )
	{
		if( parent )
			parent->RemoveChild( this );

		if( newParent )
			newParent->AddChild( this );

		//SetPosition( GetPosition() - newParent->GetPosition() );
		////SetRotation( GetRotation() - newParent->GetRotation() );
		////SetScale( GetScale() - newParent->GetScale() );

		//Matrix parentMatrixInv = newParent->GetLocalToWorldMatrix().Inverted();

		parent = newParent;
	}

	Transform * Transform::GetParent()
	{
		return this->parent;
	}
	GameObject * Transform::GetGameObject()
	{
		return this->gameObject;
	}
}