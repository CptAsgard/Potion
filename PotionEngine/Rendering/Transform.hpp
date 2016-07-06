#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include <vector>
#include <algorithm>

#include "..\Math\Matrix.hpp"
#include "..\Math\Vector3.hpp"

namespace Potion
{
	class GameObject;

	// TODO: Should use matrices instead of constructing matrix from euler and vector
	// Maybe use Quaternions?
	class Transform
	{

	public:
		Transform( GameObject* gameObject = nullptr );

		void Translate( Vector3& pos );
		void Rotate( Vector3& rot );

		void SetPosition( Vector3& pos );
		Vector3 GetPosition() const;
		//Vector3 GetWorldPosition() const;

		void SetRotation( const Vector3& rot );
		Vector3 GetRotation() const;
		//Vector3 GetWorldRotation() const;

		void SetScale( Vector3& scale );
		Vector3 GetScale() const;
		//Vector3 GetWorldScale() const;

		void LookAt( Vector3 target );

		Matrix* GetLocalToWorldMatrix();

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

		GameObject* GetGameObject();

	private:
		void RecalculateMatrix();

		Matrix GetRotationMatrix();

		std::vector< Transform* > children;
		Transform* parent;

		GameObject* gameObject;

		Matrix matrix;

		Vector3 position;
		Vector3 rotation;
		Vector3 scale;

	};
}

#endif // _TRANSFORM_H