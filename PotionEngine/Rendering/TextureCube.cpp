#include "TextureCube.hpp"

#include <stb/stb_image.h>

using namespace Potion;

TextureCube::TextureCube( const std::string& filename )
{
	Initialize( false );

	for( int i = 0; i < 6; i++ )
	{
		GLubyte* data = stbi_load( ( filename + cubeFileStrings[i] ).c_str(), &width, &height, &channels, 3 );

		if( data == nullptr )
		{
			LOG( "Image %s could not be loaded!", filename.c_str() );
		}
		else
		{
			CreateGLTextureWithData( data, false, i );

			stbi_image_free( data );
		}
	}

	Finalize( false );
}

TextureCube::~TextureCube()
{
	if( textureID )
		glDeleteTextures( 1, &textureID );

	delete[] &cubeFileStrings;
}

void TextureCube::CreateGLTextureWithData( GLubyte* data, bool genMipMaps, int index )
{
	glTexImage2D(
		GL_TEXTURE_CUBE_MAP_POSITIVE_X + index,						// What (target)
		0,									// Mip-map level
		GL_RGB,		                    // Internal format
		width,								// Width
		height,							// Height
		0,									// Border
		GL_RGB,							// Format (how to use)
		GL_UNSIGNED_BYTE,					// Type   (how to intepret)
		data );								// Data
	GL_GET_ERROR();
}



void TextureCube::Initialize( bool genMipMaps )
{
	if( textureID )
		glDeleteTextures( 1, &textureID );

	glGenTextures( 1, &textureID );											// Gen    
	GL_GET_ERROR();

	glBindTexture( GL_TEXTURE_CUBE_MAP, textureID );                                 // Bind
	GL_GET_ERROR();

	//
	if( genMipMaps )
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );    // Minmization
	else
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );                   // Minmization
	GL_GET_ERROR();

	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );                       // Magnification
	GL_GET_ERROR();


	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

	GL_GET_ERROR();
}

void Potion::TextureCube::Finalize( bool genMipMaps )
{
	if( genMipMaps )
		glGenerateMipmap( GL_TEXTURE_CUBE_MAP );

	GL_GET_ERROR();
}

void TextureCube::SetActive( int index ) const
{
	glActiveTexture( GL_TEXTURE0 + index );
	glBindTexture( GL_TEXTURE_CUBE_MAP, GetTexture() );
}