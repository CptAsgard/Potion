#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <vector>
#include <map>

#include "Shader.hpp"
#include "Color.hpp"

namespace Potion
{

	class Material
	{
	public:
		Material();
		~Material();

		void SetShader( Shader* s );
		Shader* const GetShader() const;

		void SetMainTexture( Texture* t );
		void SetTexture( const char* propertyName, Texture* t );

		void SetColor( Color col );
		Color GetColor() const;

		void ActivateForDraw();

	private:
		struct gltex_t
		{
			gltex_t( std::string name, GLint uniformLoc, Texture* tex ) : name( name ), uniformLoc( uniformLoc ), tex( tex ) {}

			std::string name;
			GLint uniformLoc;
			Texture* tex;
		};

		void ActivateTextures();
		std::vector<gltex_t> textures;

		Shader* shader;

		Color m_color;

	};

}

#endif // _MATERIAL_H