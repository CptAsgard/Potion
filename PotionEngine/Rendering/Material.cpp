#include "Material.hpp"

namespace Potion
{
	Material::Material()
	{
		if( shader == nullptr ) {
			shader = new Shader();

			shader->Attach( std::string( "../Resources/Shaders/default.frag" ), GL_FRAGMENT_SHADER );
			shader->Attach( std::string( "../Resources/Shaders/default.vert" ), GL_VERTEX_SHADER );
			shader->Link();
		}
	}

	Material::~Material()
	{
		delete shader;
	}

	void Material::SetShader( Shader* s )
	{
		this->shader = s;

		// We have to reset texture uniform locations.
		// The new shader might not have the same locations, or is missing some.
		// If it's missing we simply discard the texture
		std::vector<gltex_t> newTexArr = std::vector<gltex_t>();

		for( auto tex : this->textures ) {
			GLint uniformLoc = glGetUniformLocation( this->shader->GetProgramHandle(), tex.name.c_str() );

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
		return shader;
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

		GLint uniformLoc = glGetUniformLocation( this->shader->GetProgramHandle(), propertyName );

		if( uniformLoc == -1 ) {
			printf( "Couldn't find location of uniform '%s' in current shader!\n", propertyName );
			return;
		}

		this->textures.push_back( gltex_t( propertyName, uniformLoc, t ) );
	}

	void Material::SetColor( Color col )
	{
		if( shader == nullptr ) {
			printf( "No active shader! You can't set textures before assigning a shader.\n" );
			return;
		}

		GLint uniformLoc = glGetUniformLocation( this->shader->GetProgramHandle(), "_Color" );

		if( uniformLoc == -1 ) {
			printf( "Couldn't find location of uniform '_Color' in current shader!\n" );
			return;
		}

		this->m_color = col;
	}

	Color Material::GetColor() const
	{
		return this->m_color;
	}

	void Material::ActivateForDraw()
	{
		shader->Use();
		ActivateTextures();
	}

	void Material::ActivateTextures()
	{
		for( int i = 0; i < textures.size(); i++ ) {
			auto tex = textures[ i ];

			glActiveTexture( GL_TEXTURE0 + i );
			glBindTexture( GL_TEXTURE_2D, tex.tex->GetHandle() );
			glUniform1i( tex.uniformLoc, i );
		}
	}
}