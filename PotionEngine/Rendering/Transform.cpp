#include "Transform.hpp"

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

	Matrix Transform::GetLocalToWorldMatrix()
	{
		RecalculateMatrix();
		return m_matrix;
	}

	void Transform::RecalculateMatrix()
	{
		m_matrix = Matrix::CreateScale( m_scale.X, m_scale.Y, m_scale.Z ) * ( Matrix::CreateRotationZ( m_rotation.Z ) * Matrix::CreateRotationX( m_rotation.X ) * Matrix::CreateRotationY( m_rotation.Y ) ) * Matrix::CreateTranslation( m_position );
	}
}