#include "Shader.hpp"

#include <fstream>
#include <iostream>

namespace Potion
{

	Shader::Shader() : programHandle( -1 )
	{}

	Shader::~Shader()
	{
		Clean();
	}

	void Shader::Clean()
	{
		for( auto handle : this->attached ) {
			glDeleteShader( handle );
		}

		glDeleteProgram( this->programHandle );

		this->programHandle = -1;
		this->attached.clear();
	}

	bool Shader::Attach( std::string file, GLint mode )
	{
		std::ifstream infile;
		infile.open( file, std::ifstream::binary );

		if( !infile.is_open() ) {
			std::cout << "Couldn't open shader file!\n";
			return false;
		}

		infile.seekg( 0, std::ios::end );
		size_t fileSize = (size_t) infile.tellg();

		std::vector<char> data( fileSize + 1 ); // used to store text data
		infile.seekg( 0, std::ios::beg );

		infile.read( &data[ 0 ], fileSize );
		data[ fileSize ] = 0;

		//Cast to a const char for the gl function
		const char* fileDataConst = (const char*) &data[ 0 ];

		bool success = AttachRaw( fileDataConst, mode );

		infile.close();

		return success;
	}

	bool Shader::AttachRaw( const char* data, GLint mode )
	{
		if( this->programHandle == -1 ) {
			this->programHandle = glCreateProgram();
		}

		GLuint handle = glCreateShader( mode );

		glShaderSource( handle, 1, &data, NULL );
		glCompileShader( handle );

		GLint success;
		glGetShaderiv( handle, GL_COMPILE_STATUS, &success );
		if( success == GL_FALSE ) {
			GLchar infoLog[ 512 ];

			glGetShaderInfoLog( handle, 512, NULL, infoLog );

			glDeleteShader( handle );
			std::cout << "ERROR, SHADER COMPILATION FAILED:\n" << infoLog << std::endl;

			return false;
		}

		glAttachShader( this->programHandle, handle );
		this->attached.push_back( handle );

		return true;
	}

	void Shader::Use()
	{
		glUseProgram( this->programHandle );
	}

	bool Shader::Link()
	{
		glLinkProgram( this->programHandle );

		GLint success;
		glGetProgramiv( this->programHandle, GL_LINK_STATUS, &success );

		if( success == GL_FALSE ) {
			GLchar infoLog[ 512 ];
			glGetProgramInfoLog( this->programHandle, 512, NULL, infoLog );

			std::cout << "ERROR, SHADER > LINKING < FAILED:\n" << infoLog << std::endl;

			return false;
		}

		return true;
	}

	// Setting floats
	void Shader::SetUniform( std::string name, float* values, int count )
	{
		int loc = glGetUniformLocation( this->programHandle, name.c_str() );
		glUniform1fv( loc, count, values );
	}

	void Shader::SetUniform( std::string name, const float value )
	{
		int loc = glGetUniformLocation( this->programHandle, name.c_str() );
		glUniform1fv( loc, 1, &value );
	}

	// Setting vectors
	void Shader::SetUniform( std::string name, Vector2* vectors, int count )
	{
		int loc = glGetUniformLocation( this->programHandle, name.c_str() );
		glUniform2fv( loc, count, (GLfloat*) vectors );
	}

	void Shader::SetUniform( std::string name, const Vector2& vector )
	{
		int loc = glGetUniformLocation( this->programHandle, name.c_str() );
		glUniform2fv( loc, 1, (GLfloat*) &vector );
	}

	void Shader::SetUniform( std::string name, Vector3* vectors, int count )
	{
		int loc = glGetUniformLocation( this->programHandle, name.c_str() );
		glUniform3fv( loc, count, (GLfloat*) vectors );
	}

	void Shader::SetUniform( std::string name, const Vector3& vector )
	{
		int loc = glGetUniformLocation( this->programHandle, name.c_str() );
		glUniform3fv( loc, 1, (GLfloat*) &vector );
	}

	void Shader::SetUniform( std::string name, Vector4* vectors, int count )
	{
		int loc = glGetUniformLocation( this->programHandle, name.c_str() );
		glUniform4fv( loc, count, (GLfloat*) vectors );
	}

	void Shader::SetUniform( std::string name, const Vector4& vector )
	{
		int loc = glGetUniformLocation( this->programHandle, name.c_str() );
		glUniform4fv( loc, 1, (GLfloat*) &vector );
	}

	void Shader::SetUniform( std::string name, const Matrix& matrix )
	{
		int loc = glGetUniformLocation( this->programHandle, name.c_str() );
		glUniformMatrix4fv( loc, 1, true, matrix.values );
	}

	// Setting integers
	void Shader::SetUniform( std::string name, int* values, int count )
	{
		int loc = glGetUniformLocation( this->programHandle, name.c_str() );
		glUniform1iv( loc, count, values );
	}

	void Shader::SetUniform( std::string name, const int value )
	{
		int loc = glGetUniformLocation( this->programHandle, name.c_str() );
		glUniform1i( loc, value );
	}
}