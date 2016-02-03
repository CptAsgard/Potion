#ifndef _SHADER_H
#define _SHADER_H

#include <map>

#include <string>
#include <vector>

#include <GL\glew.h>

#include "..\Math\Vector2.hpp"
#include "..\Math\Vector2.hpp"
#include "..\Math\Matrix.hpp"

#include "Texture.hpp"

namespace Potion
{

	class Shader
	{

	public:
		Shader();
		~Shader();

		void Clean();

		bool Attach( std::string file, GLint mode );
		bool AttachRaw( const char* data, GLint mode );

		void Use();
		bool Link();

		// Setting vectors
		void SetUniform( std::string name, Vector2* vectors, int iCount = 1 );
		void SetUniform( std::string name, const Vector2& vector );
		void SetUniform( std::string name, Vector3* vectors, int iCount = 1 );
		void SetUniform( std::string name, const Vector3& vector );

		// Setting floats
		void SetUniform( std::string name, float* values, int iCount = 1 );
		void SetUniform( std::string name, const float value );

		// Setting 4x4 matrices
		void SetUniform( std::string name, const Matrix& matrix );

		// Setting textures
		void SetUniform( std::string name, const Texture& texture );

		// Setting integers
		void SetUniform( std::string name, int* values, int iCount = 1 );
		void SetUniform( std::string name, const int value );

		GLuint GetProgramHandle() const
		{
			return programHandle;
		}

	private:
		GLint programHandle;

		std::vector<GLuint> attached;

	};

}

#endif // _SHADER_H