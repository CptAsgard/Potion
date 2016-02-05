#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "..\Math\Matrix.hpp"
#include "..\Math\Vector3.hpp"

namespace Potion
{
	class Transform
	{

	public:
		Transform();

		void Translate( Vector3& pos );
		void Rotate( Vector3& rot );

		void SetPosition( Vector3& pos );
		Vector3 GetPosition() const;

		void SetRotation( Vector3& rot );
		Vector3 GetRotation() const;

		void SetScale( Vector3& scale );
		Vector3 GetScale() const;

		void LookAt( Vector3 target );

		Matrix GetLocalToWorldMatrix();

		Vector3 GetForward();

	private:
		void RecalculateMatrix();

		Matrix m_matrix;

		Vector3 m_position;
		Vector3 m_rotation;
		Vector3 m_scale;

	};
}

#endif // _TRANSFORM_H