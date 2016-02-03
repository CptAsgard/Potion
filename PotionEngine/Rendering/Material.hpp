#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <vector>
#include <map>

#include "Shader.hpp"

namespace Potion
{

	class Material
	{
	public:
		Material();
		~Material();

		void SetShader( Shader* s );
		Shader* const GetShader() const;

		void SetTexture( const char* propertyName, Texture* t );

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

	};

}

#endif // _MATERIAL_H