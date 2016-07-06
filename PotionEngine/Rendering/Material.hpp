#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <vector>
#include <map>

#include "Shader.hpp"
#include "Color.hpp"
#include "Texture.hpp"

#include "..\Systems\UniqueID.hpp"

namespace Potion
{
	enum class TranslucencyType
	{
		TT_OPAQUE = 3, // WINGDI insisted on taking OPAQUE as a #define. I'm not going to undef it.
		TT_TRANSLUCENT = 2,
		TT_TRANSLUCENT_ADDITIVE = 1,
		TT_TRANSLUCENT_SUBTRACTIVE = 0
	};

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

		void SetSpecularColor( const Color& col );
		Color GetSpecularColor() const;

		void SetShininess( float shininess );
		float GetShininess() const;

		/* TODO: GENERIC RESOURCE BEHAVIOUR */
		uint16_t GetID() const;
		//void SetID( uint16_t id );

		const std::string& GetName() const;
		void SetName( const std::string& name );
		/* ---- */

		TranslucencyType GetTranslucency() const;
		void SetTranslucency( TranslucencyType t );

		void ActivateForDraw();

	private:
		static UniqueID uniqueID;

		struct gltex_t
		{
			gltex_t( std::string name, GLint uniformLoc, Texture* tex ) : name( name ), uniformLoc( uniformLoc ), tex( tex ) {}

			std::string name;
			GLint uniformLoc;
			Texture* tex;
		};

		uint16_t id;
		std::string name;

		TranslucencyType translucency;

		void ActivateTextures();
		std::vector<gltex_t> textures;

		Shader* shader;

		Color color;
		Color specularColor;
		float shininess;

	};
}

#endif // _MATERIAL_H