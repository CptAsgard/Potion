#ifndef _MeshEntity_H
#define _MeshEntity_H

#include "..\Rendering\Mesh.hpp"
#include "..\Rendering\Camera.hpp"

#include "Entity.hpp"

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

	class MeshEntity : public Entity
	{
	public:
		MeshEntity() : m_layer( 0 ) {}

		static MeshEntity* CreatePrimitive( PrimitiveType type );

		void Render( Camera* cam );

		// takes ownership
		void SetMesh( Mesh* mesh );
		Mesh* GetMesh();

		void SetLayer( int layer );
		int GetLayer() const;

	private:
		Mesh m_mesh;

		// Used to differentiate GOs per layer
		// For example used by the Camera to draw GOs selectively
		int m_layer;
	};
}
#endif // _MeshEntity_H