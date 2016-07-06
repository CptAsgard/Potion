#pragma once

#include <vector>

#include "..\OpenGL.hpp"
#include "..\Math\Vector3.hpp"
#include "..\Math\Vector2.hpp"

namespace Potion
{

	struct VertexFormat
	{
		Vector3 Position;
		Vector3 Normal;
		Vector2 Texture;
	};

	class Mesh
	{
	public:
		/// Create an empty mesh
		Mesh();

		/// Destroy 
		~Mesh();

		/// Set the mesh vertices 
		void SetVertices( std::vector<VertexFormat>&& vertices );

		/// Set the mesh indices
		void SetIndices( std::vector<GLushort>&& indices );

		/// Call this method once you have set the vertices and indices
		/// it will create VBOs that can be rendered. It will also 
		/// clear the vertices and indices data from the CPU
		void Apply();

		/// Getter for VBO's
		const GLuint* GetVertexBuffers() const;

		const GLuint GetVertexArray() const;

		/// Determine if this mesh uses VBO's
		bool HasVertexBuffers() const;

		/// Get the nummber of indieces
		uint GetIndexCount() const;

		/// Only valid if the mesh is not ready to be rendered yet
		std::vector<VertexFormat> GetVertices() const { return vertices; }

		/// Only valid if the mesh is not ready to be rendered yet
		std::vector<GLushort>	GetIndices() const { return	indices; }

	protected:

		/// Mesh vertices, stored temporary when loading or creating a mesh
		std::vector<VertexFormat>    vertices;

		/// Mesh indices, stored temporary when loading or creating a mesh
		std::vector<GLushort>		indices;

		/// Primitive count
		uint						indexCount;

		/// Vertex buffers object
		/// [0] is vertices
		/// [1] is indices
		GLuint						vbo[ 2 ];

		GLuint						vao;
	};

}
