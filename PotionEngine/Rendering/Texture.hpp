#pragma once

#include <vector>

#include "..\OpenGL.hpp"

namespace Potion
{

	class Texture
	{
	public:

		/// Create a texture by loading from a file
		/// Uses stb_image (as SOIL does). Check for supported formats
		/// in the stb_image header
		Texture( const std::string& filename );

		/// Creates an empty texture with given size. You will need to provide
		/// the data.
		Texture( int width, int height );

		/// Releases OpenGL resources
		virtual ~Texture();

		/// Get the texture ID in OpenGL
		GLuint GetTexture() const { return textureID; }

		/// Sets the texture as the active texture
		virtual void SetActive( int index = 0 ) const;

		/// Creates a texture from RGBA provided data
		virtual void CreateGLTextureWithData( GLubyte* data, bool genMipMaps );

	protected:
		/// Used for the label
		Texture() {}

		void Initialize( bool genMipMaps );
		void Finalize( bool genMipMaps );

		GLuint textureID = 0;
		int width = 0;
		int height = 0;
		int channels = 0;
	};

}
