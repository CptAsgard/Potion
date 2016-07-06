#include "Material.hpp"

namespace Potion
{
	UniqueID Material::uniqueID;

	Material::Material() : 
		color( Color( 255, 255, 255 ) ), 
		specularColor( Color( 255, 255, 255 ) ), 
		shininess( 1.f ),
		translucency( Potion::TranslucencyType::TT_OPAQUE )
	{
		shader = new Shader( "Assets/Basic.vsh", "Assets/Basic.fsh" );

		this->id = Material::uniqueID.GetNext();
	}

	Material::~Material()
	{
		Material::uniqueID.Free( this->id );
		delete shader;

		for( int i = 0; i < textures.size(); i++ )
		{
			delete textures[ i ].tex;
		}
	}

	void Material::SetShader( Shader* s )
	{
		this->shader = s;

		// We have to reset texture uniform locations.
		// The new shader might not have the same locations, or is missing some.
		// If it's missing we simply discard the texture
		std::vector<gltex_t> newTexArr = std::vector<gltex_t>();

		for( auto tex : this->textures ) {
			GLint uniformLoc = glGetUniformLocation( this->shader->GetProgram(), tex.name.c_str() );

			if( uniformLoc != -1 ) {
				newTexArr.push_back( tex );
			} else {
				printf( "Shader WARNING: Couldn't find new handle\n" );
			}
		}

		this->textures = newTexArr;
	}

	Shader* const Material::GetShader() const
	{
		return this->shader;
	}

	void Material::SetMainTexture( Texture * t )
	{
		SetTexture( "_MainTex", t );
	}

	void Material::SetTexture( const char* propertyName, Texture* t )
	{
		if( shader == nullptr ) {
			printf( "No active shader! You can't set textures before assigning a shader.\n" );
			return;
		}

		GLint uniformLoc = glGetUniformLocation( this->shader->GetProgram(), propertyName );

		if( uniformLoc == -1 ) {
			printf( "Couldn't find location of uniform '%s' in current shader '%s'!\n", propertyName, this->shader->_name.c_str() );
			return;
		}

		this->textures.push_back( gltex_t( propertyName, uniformLoc, t ) );
	}

	void Material::SetColor( Color col )
	{
		this->color = col;
	}

	Color Material::GetColor() const
	{
		return this->color;
	}

	void Material::SetSpecularColor( const Color & col )
	{
		this->specularColor = col;
	}

	Color Material::GetSpecularColor() const
	{
		return this->specularColor;
	}

	void Material::SetShininess( float shininess )
	{
		this->shininess = shininess;
	}

	float Material::GetShininess() const
	{
		return this->shininess;
	}

	uint16_t Material::GetID() const
	{
		return this->id;
	}

	const std::string & Material::GetName() const
	{
		return this->name;
	}

	void Material::SetName( const std::string & name )
	{
		this->name = name;
	}

	//void Material::SetID( uint16_t id )
	//{
	//	m_id = id;
	//}

	TranslucencyType Material::GetTranslucency() const
	{
		return this->translucency;
	}

	void Material::SetTranslucency( TranslucencyType t )
	{
		this->translucency = t;
	}

	void Material::ActivateForDraw()
	{
		GetShader()->Activate();
		ActivateTextures();
	}

	void Material::ActivateTextures()
	{
		for( int i = 0; i < textures.size(); i++ ) {
			auto tex = textures[ i ];

			tex.tex->SetActive( i );
			glUniform1i( tex.uniformLoc, i );
		}
	}
}