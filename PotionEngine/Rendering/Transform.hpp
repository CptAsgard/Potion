#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include <vector>
#include <algorithm>

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
		Vector3 GetWorldPosition() const;

		void SetRotation( const Vector3& rot );
		Vector3 GetRotation() const;
		Vector3 GetWorldRotation() const;

		void SetScale( Vector3& scale );
		Vector3 GetScale() const;
		Vector3 GetWorldScale() const;

		void LookAt( Vector3 target );

		Matrix GetLocalToWorldMatrix();

		Vector3 GetForward();

		// To be used by other Transforms for bookkeeping.
		// DON'T USE THIS. Use SetParent().
		void AddChild( Transform* obj );

		// To be used by other Transforms for bookkeeping.
		// DON'T USE THIS. Use SetParent().
		void RemoveChild( Transform* obj );

		Transform* GetChild( int index );

		unsigned int GetChildCount() const;

		void SetParent( Transform* parent );
		Transform* GetParent();

	private:
		void RecalculateMatrix();

		Matrix GetWorldRotationMatrix();

		std::vector< Transform* > m_children;
		Transform* m_parent;

		Matrix m_matrix;

		Vector3 m_position;
		Vector3 m_rotation;
		Vector3 m_scale;

	};
}

#endif // _TRANSFORM_H