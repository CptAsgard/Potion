#include <map>
#include <sstream>

#include "Mesh.hpp"
#include "..\Utils\Defines.hpp"
#include "..\Utils\Utils.hpp"

using namespace Potion;

Mesh::Mesh() : indexCount( 0 ), vbo{ 0, 0 }, vao( 0 )
{}

Potion::Mesh::~Mesh()
{
	if( HasVertexBuffers() )
	{
		glDeleteBuffers( 2, vbo );
		GL_GET_ERROR();
	}

	glDeleteVertexArrays( 1, &vao );
	GL_GET_ERROR();
}

void Mesh::SetVertices( std::vector<VertexFormat>&& vertices )
{
	this->vertices = std::move( vertices );
}

void Mesh::SetIndices( std::vector<GLushort>&& indices )
{
	this->indices = std::move( indices );
}

void Mesh::Apply()
{
	// Allocate a VAO
	glGenVertexArrays( 1, &vao );

	// Allocate two buffers
	glGenBuffers( 2, vbo );
	GL_GET_ERROR();

	// VAO
	glBindVertexArray( vao );

	// Array buffer contains the attribute data
	glBindBuffer( GL_ARRAY_BUFFER, vbo[ 0 ] );
	GL_GET_ERROR();

	// Copy into VBO
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices[ 0 ] ) * vertices.size(), &vertices[ 0 ], GL_STATIC_DRAW );
	GL_GET_ERROR();

	// Element array buffer contains the indices.
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vbo[ 1 ] );
	GL_GET_ERROR();

	// Copy into VBO
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices[ 0 ] ) * indices.size(), &indices[ 0 ], GL_STATIC_DRAW );
	GL_GET_ERROR();

	// Start VAO setup

	const void* firstPosition = reinterpret_cast<const void*>(offsetof( VertexFormat, Position ));
	const void* firstNormal = reinterpret_cast<const void*>(offsetof( VertexFormat, Normal ));
	const void* firstTexture = reinterpret_cast<const void*>(offsetof( VertexFormat, Texture ));

	GLsizei size = sizeof( VertexFormat );

	// Vertex Positions
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, size,
		firstPosition );
	// Vertex Normals
	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, size,
		firstNormal );
	// Vertex Texture Coords
	glEnableVertexAttribArray( 2 );
	glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, size,
		firstTexture );

	GL_GET_ERROR();

	// VAO setup done

	glBindVertexArray( 0 );
	GL_GET_ERROR();

	indexCount = static_cast<uint>(indices.size());
	vertices.clear();
	indices.clear();
}

const GLuint* Mesh::GetVertexBuffers() const
{
	return this->vbo;
}

const GLuint Potion::Mesh::GetVertexArray() const
{
	return this->vao;
}

bool Mesh::HasVertexBuffers() const
{
	return this->vbo[ 0 ] != 0 && this->vbo[ 1 ] != 0;
}

uint Mesh::GetIndexCount() const
{
	return this->indexCount;
}