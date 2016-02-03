#ifndef _MESH_H
#define _MESH_H

#include <GL\glew.h>

#include "Shader.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "Transform.hpp"

#include "..\Math\Vector2.hpp"
#include "..\Math\Vector3.hpp"
#include "..\Math\Matrix.hpp"

namespace Potion
{

	struct Vertex
	{
		Vertex() {}
		Vertex( Vector3 pos, Vector2 uv, Vector3 color = Vector3( 0, 0, 0 ) ) : position( pos ), color( color ), UV( uv )
		{ }

		Vector3 position;
		Vector3 color;
		Vector2 UV;
	};

	class Mesh
	{

	public:
		Mesh( Material* m = nullptr );
		~Mesh();

		void ApplyVertices( Vertex* vertices, unsigned int count );

		void ApplyIndices( GLuint* indices, unsigned int count );

		void SetMaterial( Material* m );
		Material* const GetMaterial();

		void Mesh::Draw( const Matrix& MVP );

		Transform transform;

	private:
		void SetGL();

		Material* material;

		GLuint vao;
		GLuint vbo;
		GLuint ebo;

		unsigned int vertexCount;
		unsigned int indicesCount;

	};

}

#endif // _MESH_H