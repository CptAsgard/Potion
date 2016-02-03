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

	Material* const Mesh::GetMaterial()
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

		GLint colorAttrib = glGetAttribLocation( material->GetShader()->GetProgramHandle(), "vertexColor" );
		glEnableVertexAttribArray( colorAttrib );
		glVertexAttribPointer( colorAttrib, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*) offsetof( Vertex, color ) );

		GLint uvAttrib = glGetAttribLocation( material->GetShader()->GetProgramHandle(), "texCoord" );
		glEnableVertexAttribArray( uvAttrib );
		glVertexAttribPointer( uvAttrib, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*) offsetof( Vertex, UV ) );

		glBindVertexArray( 0 );
	}

	void Mesh::Draw( const Matrix& MVP )
	{
		MVP.DebugPrint();

		GetMaterial()->GetShader()->SetUniform( std::string( "POT_MATRIX_MVP" ), MVP );

		material->ActivateForDraw();

		glBindVertexArray( this->vao );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->ebo );

		//glDrawElements( GL_TRIANGLES, this->indicesCount, GL_UNSIGNED_INT, 0 );
		glDrawArrays( GL_TRIANGLES, 0, 36 );

		glBindVertexArray( 0 );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	}

}