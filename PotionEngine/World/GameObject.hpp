#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "..\Rendering\Transform.hpp"
#include "..\Rendering\Mesh.hpp"
#include "..\Rendering\Camera.hpp"

namespace Potion
{
	enum PrimitiveType
	{
		SPHERE,
		CAPSULE,
		CYLINDER,
		CUBE,
		PLANE,
		QUAD
	};

	class Camera;

	class GameObject
	{
	public:
		GameObject();

		static GameObject* CreatePrimitive( PrimitiveType type );

		void Draw( Camera* cam );

		Mesh mesh;
		Transform transform;

	};
}

#endif // _GAMEOBJECT_H