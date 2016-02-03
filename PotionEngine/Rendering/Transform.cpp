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
		m_position += pos;
		RecalculateMatrix();
	}

	void Transform::Rotate( Vector3 & rot )
	{
		m_rotation += rot;
		RecalculateMatrix();
	}

	void Transform::SetPosition( Vector3 & pos )
	{
		m_position = pos;
		RecalculateMatrix();
	}

	Vector3 Transform::GetPosition() const
	{
		return m_position;
	}

	void Transform::SetRotation( Vector3 & rot )
	{
		m_rotation = rot;
		RecalculateMatrix();
	}

	Vector3 Transform::GetRotation() const
	{
		return m_rotation;
	}

	void Transform::SetScale( Vector3 & scale )
	{
		m_scale = scale;
		RecalculateMatrix();
	}

	Vector3 Transform::GetScale() const
	{
		return m_scale;
	}

	void Transform::SetWorldMatrix( Matrix m )
	{
		m_matrix = m;
	}

	Matrix Transform::GetLocalToWorldMatrix() const
	{
		return m_matrix;
	}

	void Transform::RecalculateMatrix()
	{
		m_matrix = Matrix::CreateScale( m_scale.X, m_scale.Y, m_scale.Z ) * Matrix::CreateTranslation( m_position ) * Matrix::CreateRotationZ( m_rotation.Z ) * Matrix::CreateRotationY( m_rotation.Y ) * Matrix::CreateRotationX( m_rotation.X );
	}
}