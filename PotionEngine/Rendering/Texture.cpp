#include "Texture.hpp"

#include <iostream>
#include <vector>

#include "..\Libraries\lodepng.h"

namespace Potion
{
	Texture::Texture() :
		Handle( -1 ),
		width( 0 ),
		height( 0 )
	{
		glGenTextures( 1, &this->Handle );
		BindGL();
	}

	Texture::Texture( std::string path ) :
		Handle( -1 ),
		width( 0 ),
		height( 0 )
	{
		glGenTextures( 1, &this->Handle );
		LoadFromFile( path );
		BindGL();
	}

	Texture::~Texture()
	{
		Clear();
	}

	bool Texture::LoadFromFile( std::string path )
	{
		unsigned error = lodepng::decode( this->rawImg, this->width, this->height, path );

		if( error != 0 ) {
			std::cout << "decoder error " << error << ": " << lodepng_error_text( error ) << std::endl;
			return false;
		}

		Apply();

		return true;
	}

	void Texture::BindGL()
	{
		glBindTexture( GL_TEXTURE_2D, this->Handle );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

		glBindTexture( GL_TEXTURE_2D, 0 );
	}

	void Texture::Apply()
	{
		glBindTexture( GL_TEXTURE_2D, this->Handle );

		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &this->rawImg[ 0 ] );
		glGenerateMipmap( GL_TEXTURE_2D );

		glBindTexture( GL_TEXTURE_2D, 0 );
	}

	void Texture::Use()
	{
		glBindTexture( GL_TEXTURE_2D, this->Handle );
	}

	void Texture::Clear()
	{
		glDeleteTextures( 1, &this->Handle );
	}
}