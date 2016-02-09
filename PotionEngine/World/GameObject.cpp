#include "GameObject.hpp"

namespace Potion
{
	GameObject::GameObject()
	{}

	GameObject* GameObject::CreatePrimitive( PrimitiveType type )
	{
		GameObject* go = new GameObject();

		Vertex verts[] = {
			Vertex( Vector3( -1.0f, -1.0f, 1.0f ), Vector2( 0.0f, 1.0f ), Vector3( 0.f, 0.f, 1.0f ) ),
			Vertex( Vector3( 1.0f, -1.0f, 1.0f ), Vector2( 1.0f, 1.0f ), Vector3( 0.f, 0.f, 1.0f ) ),
			Vertex( Vector3( 1.0f, 1.0f, 1.0f ), Vector2( 1.0f, 0.0f ), Vector3( 0.f, 0.f, 1.0f ) ),
			Vertex( Vector3( -1.0f, 1.0f, 1.0f ), Vector2( 0.0f, 0.0f ), Vector3( 0.f, 0.f, 1.0f ) ),

			Vertex( Vector3( 1.0f, -1.0f, 1.0f ), Vector2( 0.0f, 1.0f ), Vector3( 1.0f, 0.0f, 0.0f ) ),
			Vertex( Vector3( 1.0f, -1.0f, -1.0f ), Vector2( 1.0f, 1.0f ), Vector3( 1.0f, 0.0f, 0.0f ) ),
			Vertex( Vector3( 1.0f, 1.0f, -1.0f ), Vector2( 1.0f, 0.0f ), Vector3( 1.0f, 0.0f, 0.0f ) ),
			Vertex( Vector3( 1.0f, 1.0f, 1.0f ), Vector2( 0.0f, 0.0f ), Vector3( 1.0f, 0.0f, 0.0f ) ),

			Vertex( Vector3( 1.0f, -1.0f, -1.0f ), Vector2( 0.0f, 1.0f ), Vector3( 0.0f, 0.0f, -1.0f ) ),
			Vertex( Vector3( -1.0f, -1.0f, -1.0f ), Vector2( 1.0f, 1.0f ), Vector3( 0.0f, 0.0f, -1.0f ) ),
			Vertex( Vector3( -1.0f, 1.0f, -1.0f ), Vector2( 1.0f, 0.0f ), Vector3( 0.0f, 0.0f, -1.0f ) ),
			Vertex( Vector3( 1.0f, 1.0f, -1.0f ), Vector2( 0.0f, 0.0f ), Vector3( 0.0f, 0.0f, -1.0f ) ),

			Vertex( Vector3( -1.0f, -1.0f, -1.0f ), Vector2( 0.0f, 1.0f ), Vector3( -1.0f, 0.0f, 0.0f ) ),
			Vertex( Vector3( -1.0f, -1.0f, 1.0f ), Vector2( 1.0f, 1.0f ), Vector3( -1.0f, 0.0f, 0.0f ) ),
			Vertex( Vector3( -1.0f, 1.0f, 1.0f ), Vector2( 1.0f, 0.0f ), Vector3( -1.0f, 0.0f, 0.0f ) ),
			Vertex( Vector3( -1.0f, 1.0f, -1.0f ), Vector2( 0.0f, 0.0f ), Vector3( -1.0f, 0.0f, 0.0f ) ),

			Vertex( Vector3( -1.0f, 1.0f, 1.0f ), Vector2( 0.0f, 1.0f ), Vector3( 0.0f, 1.0f, 0.0f ) ),
			Vertex( Vector3( 1.0f, 1.0f, 1.0f ), Vector2( 1.0f, 1.0f ), Vector3( 0.0f, 1.0f, 0.0f ) ),
			Vertex( Vector3( 1.0f, 1.0f, -1.0f ), Vector2( 1.0f, 0.0f ), Vector3( 0.0f, 1.0f, 0.0f ) ),
			Vertex( Vector3( -1.0f, 1.0f, -1.0f ), Vector2( 0.0f, 0.0f ), Vector3( 0.0f, 1.0f, 0.0f ) ),

			Vertex( Vector3( 1.0f, -1.0f, 1.0f ), Vector2( 0.0f, 1.0f ), Vector3( 0.0f, -1.0f, 0.0f ) ),
			Vertex( Vector3( -1.0f, -1.0f, 1.0f ), Vector2( 1.0f, 1.0f ), Vector3( 0.0f, -1.0f, 0.0f ) ),
			Vertex( Vector3( -1.0f, -1.0f, -1.0f ), Vector2( 1.0f, 0.0f ), Vector3( 0.0f, -1.0f, 0.0f ) ),
			Vertex( Vector3( 1.0f, -1.0f, -1.0f ), Vector2( 0.0f, 0.0f ), Vector3( 0.0f, -1.0f, 0.0f ) )
		};

		GLuint indices[] = {
			// Font face
			0, 1, 2, 2, 3, 0,
			// Right face
			7, 6, 5, 5, 4, 7,
			// Back face
			11, 10, 9, 9, 8, 11,
			// Left face
			15, 14, 13, 13, 12, 15,
			// Top Face	
			19, 18, 17, 17, 16, 19,
			// Bottom Face
			23, 22, 21, 21, 20, 23
		};

		go->mesh.ApplyVertices( verts, 24 );
		go->mesh.ApplyIndices( indices, 36 );

		return go;
	}

	void GameObject::Draw( Camera* cam )
	{
		mesh.GetMaterial()->GetShader()->SetUniform( std::string( "_Object2World" ), transform.GetLocalToWorldMatrix() );
		mesh.GetMaterial()->GetShader()->SetUniform( std::string( "_Normal2World" ), transform.GetLocalToWorldMatrix().Inverted().Mirror() );

		// foreach attached mesh
		mesh.GLDraw( cam->TransformModelMatrixToMVP( transform.GetLocalToWorldMatrix() ) );
	}
}