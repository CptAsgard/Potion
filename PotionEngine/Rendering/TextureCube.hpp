#pragma once

#include <vector>

#include "Texture.hpp"

namespace Potion
{

	class TextureCube : public Texture
	{
	public:

		/// Create a texture by loading from a file
		/// Uses stb_image (as SOIL does). Check for supported formats
		/// in the stb_image header
		TextureCube( const std::string& filename );

		/// Releases OpenGL resources
		~TextureCube();

		/// Get the texture ID in OpenGL
		GLuint GetTexture() const { return textureID; }

		/// Creates a texture from RGBA provided data
		void CreateGLTextureWithData( GLubyte* data, bool genMipMaps, int index );

		/// Sets the texture as the active texture
		virtual void SetActive( int index ) const override;

	protected:
		void Initialize( bool genMipMaps );
		void Finalize( bool genMipMaps );

		// TODO: Cubes shouldn't be bound to jpg
		std::string cubeFileStrings[6] = { "_right.jpg", "_left.jpg", "_top.jpg", "_bottom.jpg", "_back.jpg", "_front.jpg" };

		/// Used for the label
		TextureCube() {}

	};

}
