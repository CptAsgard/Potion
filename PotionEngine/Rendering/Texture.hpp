#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <string>
#include <vector>
#include <gl\glew.h>

namespace Potion
{

	class Texture
	{
	public:
		Texture();
		Texture( std::string path );
		~Texture();

		bool LoadFromFile( std::string path );

		void BindGL();
		void Apply();
		void Use();
		void Clear();

		GLuint GetHandle() const
		{
			return Handle;
		}

	private:
		GLuint Handle;
		unsigned int width, height;

		std::vector<unsigned char> rawImg;
	};

}
#endif // _TEXTURE_H