#include "TextureRender.hpp"

#include <stb/stb_image.h>

using namespace Potion;

TextureRender::TextureRender( int width, int height ) : Texture( width, height )
{
	Initialize( false );

	Finalize( false );
}

TextureRender::~TextureRender()
{
	glDeleteFramebuffers( 1, &frameBufferID );

	Texture::~Texture();
}

void TextureRender::SetBufferActive( int index ) const
{
	glBindFramebuffer( GL_FRAMEBUFFER, frameBufferID );
	//glBindRenderbuffer( GL_RENDERBUFFER, _renderBuffer );
}

void Potion::TextureRender::SetBufferInactive() const
{
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
	//glBindRenderbuffer( GL_RENDERBUFFER, 0 );
}

void TextureRender::Initialize( bool genMipMaps )
{
	Texture::Initialize( genMipMaps );

	glTexImage2D(
		GL_TEXTURE_2D,						// What (target)
		0,									// Mip-map level
		GL_RGB,		                    // Internal format
		width,								// Width
		height,							// Height
		0,									// Border
		GL_RGB,							    // Format (how to use)
		GL_UNSIGNED_BYTE,					// Type   (how to intepret)
		NULL );								// Data
	GL_GET_ERROR();

	Texture::Finalize( genMipMaps );

	// Framebuffer
	glGenFramebuffers( 1, &frameBufferID );
	GL_GET_ERROR();

	glBindFramebuffer( GL_FRAMEBUFFER, frameBufferID );
	GL_GET_ERROR();

	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0 );

	// Renderbuffer
	glGenRenderbuffers( 1, &renderBufferID );
	GL_GET_ERROR();

	glBindRenderbuffer( GL_RENDERBUFFER, renderBufferID );

	glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height );

	glBindRenderbuffer( GL_RENDERBUFFER, 0 );

	glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferID );

	if( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
		printf( "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n" );

	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void TextureRender::Finalize( bool genMipMaps )
{
	//if( genMipMaps )
	//	glGenerateMipmap( GL_TEXTURE_CUBE_MAP );

	//GL_GET_ERROR();
}