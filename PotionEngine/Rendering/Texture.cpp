#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

using namespace Potion;

Texture::Texture( const std::string& filename )
{
	GLubyte* data = stbi_load( filename.c_str(), &width, &height, &channels, 4 );

	if( data == nullptr )
	{
		LOG( "Image %s could not be loaded!", filename.c_str() );
	}
	else
	{
		CreateGLTextureWithData( data, true );
		stbi_image_free( data );
	}
}

Texture::Texture( int width, int height ) : textureID( 0 ), width( width ), height( height ) {}

Texture::~Texture()
{
	if( textureID )
		glDeleteTextures( 1, &textureID );
}

void Texture::CreateGLTextureWithData( GLubyte* data, bool genMipMaps )
{
	Initialize( genMipMaps );

	glTexImage2D(
		GL_TEXTURE_2D,						// What (target)
		0,									// Mip-map level
		GL_RGBA,		                    // Internal format
		width,								// Width
		height,							// Height
		0,									// Border
		GL_RGBA,							// Format (how to use)
		GL_UNSIGNED_BYTE,					// Type   (how to intepret)
		data );								// Data
	GL_GET_ERROR();

	Finalize( genMipMaps );
}

void Texture::SetActive( int index ) const
{
	glActiveTexture( GL_TEXTURE0 + index );
	glBindTexture( GL_TEXTURE_2D, GetTexture() );
}

void Texture::Initialize( bool genMipMaps )
{
	if( textureID )
		glDeleteTextures( 1, &textureID );

	glGenTextures( 1, &textureID );											// Gen    
	GL_GET_ERROR();

	glBindTexture( GL_TEXTURE_2D, textureID );                                 // Bind
	GL_GET_ERROR();
}

void Texture::Finalize( bool genMipMaps )
{
	if( genMipMaps )
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );    // Minmization
	else
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );                   // Minmization
	GL_GET_ERROR();

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );                       // Magnification
	GL_GET_ERROR();

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	GL_GET_ERROR();

	if( genMipMaps )
		glGenerateMipmap( GL_TEXTURE_2D );

	glBindTexture( GL_TEXTURE_2D, 0 );
	GL_GET_ERROR();
}