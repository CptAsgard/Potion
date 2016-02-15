#include "Mesh.hpp"

#include "..\Util.hpp"

#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

#include <cstddef>

namespace Potion
{
	Mesh::Mesh( Material* m )
	{
		if( m == nullptr ) {
			m = new Material();
		}

		this->material = m;

		glGenBuffers( 1, &this->vbo );
		glGenBuffers( 1, &this->ebo );
		glGenVertexArrays( 1, &this->vao );

		SetGL();
	}

	Mesh::~Mesh()
	{
		delete material;

		glDeleteVertexArrays( 1, &this->vao );
		glDeleteBuffers( 1, &this->vbo );
		glDeleteBuffers( 1, &this->ebo );
	}

	Mesh* Mesh::CreatePrimitive( PrimitiveType type )
	{
		Mesh* mesh = new Mesh();

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

		mesh->ApplyVertices( verts, 24 );
		mesh->ApplyIndices( indices, 36 );

		return mesh;
	}

	void Mesh::ApplyVertices( Vertex* vertices, unsigned int count )
	{
		this->vertexCount = count;

		glBindBuffer( GL_ARRAY_BUFFER, this->vbo );
		glBufferData( GL_ARRAY_BUFFER, this->vertexCount * sizeof( Vertex ), vertices, GL_STATIC_DRAW );
	}

	void Mesh::ApplyIndices( GLuint* indices, unsigned int count )
	{
		this->indicesCount = count;

		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->ebo );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, this->indicesCount * sizeof( GLuint ), indices, GL_STATIC_DRAW );
	}

	void Mesh::SetMaterial( Material* m )
	{
		this->material = m;

		SetGL();
	}

	Material* Mesh::GetMaterial()
	{
		return this->material;
	}

	void Mesh::SetGL()
	{
		material->GetShader()->Use();

		glBindVertexArray( this->vao );

		glBindBuffer( GL_ARRAY_BUFFER, this->vbo );

		GLint posAttrib = glGetAttribLocation( material->GetShader()->GetProgramHandle(), "position" );
		glEnableVertexAttribArray( posAttrib );
		glVertexAttribPointer( posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*) offsetof( Vertex, position ) );

		GLint colorAttrib = glGetAttribLocation( material->GetShader()->GetProgramHandle(), "color" );
		glEnableVertexAttribArray( colorAttrib );
		glVertexAttribPointer( colorAttrib, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*) offsetof( Vertex, color ) );

		GLint uvAttrib = glGetAttribLocation( material->GetShader()->GetProgramHandle(), "uv" );
		glEnableVertexAttribArray( uvAttrib );
		glVertexAttribPointer( uvAttrib, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*) offsetof( Vertex, UV ) );

		GLint normalAttrib = glGetAttribLocation( material->GetShader()->GetProgramHandle(), "normal" );
		glEnableVertexAttribArray( normalAttrib );
		glVertexAttribPointer( normalAttrib, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*) offsetof( Vertex, normal ) );

		glBindVertexArray( 0 );
	}

	void Mesh::GLDraw( const Matrix& MVP )
	{
		GetMaterial()->GetShader()->SetUniform( std::string( "POT_MATRIX_MVP" ), MVP );

		material->ActivateForDraw();

		glBindVertexArray( this->vao );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->ebo );

		glDrawElements( GL_TRIANGLES, this->indicesCount, GL_UNSIGNED_INT, 0 );

		glBindVertexArray( 0 );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	}
}