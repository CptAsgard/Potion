#pragma once

#include <vector>

#include "Texture.hpp"

namespace Potion
{
	class TextureRender : public Texture
	{
	public:

		/// Create a render texture
		TextureRender( int width, int height );

		/// Releases OpenGL resources
		~TextureRender();

		/// Get the texture ID in OpenGL
		GLuint GetTexture() const { return textureID; }

		/// Creates a texture from RGBA provided data
		void CreateGLTextureWithData( GLubyte* data, bool genMipMaps, int index );

		/// Sets the texture as the active texture
		virtual void SetBufferActive( int index = 0 ) const;

		virtual void SetBufferInactive() const;

	protected:
		void Initialize( bool genMipMaps );
		void Finalize( bool genMipMaps );

		GLuint frameBufferID;
		GLuint renderBufferID;

	};

}
