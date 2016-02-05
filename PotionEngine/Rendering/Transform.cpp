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
		//m_position += m_matrix.Translate( pos );
		m_position += (m_matrix.Translate( pos ) - m_matrix.GetTranslation());
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

	void Transform::SetRotation( Vector3 & rot )
	{
		m_rotation = rot;
	}

	Vector3 Transform::GetRotation() const
	{
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

	void Transform::LookAt( Vector3 target )
	{
		Vector3 lookDir = ( target - m_position ).Normalized();

		float lookLengthOnXZ = sqrtf( lookDir.Z*lookDir.Z + lookDir.X*lookDir.X );
		float m_rotationX = -RadToDeg( atan2f( lookDir.Y, lookLengthOnXZ ) );
		float m_rotationY = RadToDeg( atan2f( lookDir.X, lookDir.Z ) );

		SetRotation( Vector3( m_rotationX, m_rotationY, GetRotation().Z ) );

		RecalculateMatrix();
	}

	Matrix Transform::GetLocalToWorldMatrix()
	{
		RecalculateMatrix();
		return m_matrix;
	}

	Vector3 Transform::GetForward()
	{
		Matrix temp = (Matrix::CreateRotationZ( m_rotation.Z ) * Matrix::CreateRotationY( m_rotation.Y ) * Matrix::CreateRotationX( m_rotation.X ));
		return temp.Translate( Vector3( 0, 0, 1 ) );
	}

	void Transform::RecalculateMatrix()
	{
		m_matrix = Matrix::CreateScale( m_scale.X, m_scale.Y, m_scale.Z ) * ( Matrix::CreateRotationZ( m_rotation.Z ) * Matrix::CreateRotationY( m_rotation.Y ) * Matrix::CreateRotationX( m_rotation.X ) ) * Matrix::CreateTranslation( m_position );
	}
}