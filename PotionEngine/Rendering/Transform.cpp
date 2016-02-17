#include "Transform.hpp"
#include "..\Util.hpp"

#include <math.h>
#include <cfloat>

namespace Potion
{
	Transform::Transform()
	{
		SetPosition( Vector3( 0, 0, 0 ) );
		SetRotation( Vector3( 0, 0, 0 ) );
		SetScale( Vector3( 1, 1, 1 ) );
	}

	void Transform::Translate( Vector3 & pos )
	{
		pos = GetWorldRotationMatrix().Translate( pos );

		m_position += pos;
	}

	void Transform::Rotate( Vector3 & rot )
	{
		m_rotation += rot;
	}

	void Transform::SetPosition( Vector3 & pos )
	{
		m_position = pos;
	}

	Vector3 Transform::GetPosition() const
	{
		return m_position;
	}

	Vector3 Transform::GetWorldPosition() const
	{
		if( m_parent )
			return m_parent->GetWorldPosition() + m_position;
		else
			return m_position;
	}

	void Transform::SetRotation( const Vector3 & rot )
	{
		m_rotation = rot;
	}

	Vector3 Transform::GetRotation() const
	{
		return m_rotation;
	}

	Vector3 Transform::GetWorldRotation() const
	{
		if( m_parent )
			return m_parent->GetWorldRotation() + m_rotation;
		else
			return m_rotation;
	}

	void Transform::SetScale( Vector3 & scale )
	{
		m_scale = scale;
	}

	Vector3 Transform::GetScale() const
	{
		return m_scale;
	}

	Vector3 Transform::GetWorldScale() const
	{
		if( m_parent )
			return m_parent->GetWorldScale() + m_scale;
		else
			return m_scale;
	}

	void Transform::LookAt( Vector3 target )
	{
		Vector3 lookDir = ( target - GetWorldPosition() ).Normalized();

		float lookLengthOnXZ = sqrtf( lookDir.Z*lookDir.Z + lookDir.X*lookDir.X );
		float m_rotationX = -RadToDeg( atan2f( lookDir.Y, lookLengthOnXZ ) );
		float m_rotationY = RadToDeg( atan2f( lookDir.X, lookDir.Z ) );

		SetRotation( Vector3( m_rotationX, m_rotationY, GetWorldRotation().Z ) );

		RecalculateMatrix();
	}

	Matrix Transform::GetLocalToWorldMatrix()
	{
		RecalculateMatrix();
		return m_matrix;
	}

	Vector3 Transform::GetForward()
	{
		return GetWorldRotationMatrix().Translate( Vector3( 0, 0, 1 ) );
	}

	void Transform::RecalculateMatrix()
	{
		m_matrix = Matrix::CreateTranslation( GetWorldPosition() ) * GetWorldRotationMatrix() * Matrix::CreateScale( GetWorldScale() );
	}

	Matrix Transform::GetWorldRotationMatrix()
	{
		Vector3 worldRotation = GetWorldRotation();
		return ( Matrix::CreateRotationZ( worldRotation.Z ) * Matrix::CreateRotationY( worldRotation.Y ) * Matrix::CreateRotationX( worldRotation.X ) );
	}

	void Transform::AddChild( Transform * obj )
	{
		m_children.push_back( obj );
	}

	void Transform::RemoveChild( Transform * obj )
	{
		if( m_children.size() < 1 )
			return;

		auto it = std::remove( m_children.begin(), m_children.end(), obj );

		if( it != m_children.end() )
			m_children.erase( it, m_children.end() );
	}

	Transform * Transform::GetChild( int index )
	{
		return m_children[ index ];
	}

	unsigned int Transform::GetChildCount() const
	{
		return m_children.size();
	}

	void Transform::SetParent( Transform * newParent )
	{
		if( m_parent )
			m_parent->RemoveChild( this );

		if( newParent )
			newParent->AddChild( this );

		SetPosition( GetWorldPosition() - newParent->GetWorldPosition() );
		SetRotation( GetWorldRotation() - newParent->GetWorldRotation() );
		SetScale( GetWorldScale() - newParent->GetWorldScale() );

		m_parent = newParent;
	}

	Transform * Transform::GetParent()
	{
		return m_parent;
	}
}