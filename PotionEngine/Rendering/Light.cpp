#include "Light.hpp"

namespace Potion
{
	Light::Light() : Entity()
	{
		//GetMesh->GetMaterial()->SetShader( new Shader() );
		//GetMesh->GetMaterial()->GetShader()->Attach( "../Resources/Shaders/lightEntity.frag", GL_FRAGMENT_SHADER );
		//GetMesh->GetMaterial()->GetShader()->Attach( "../Resources/Shaders/lightEntity.vert", GL_VERTEX_SHADER );
		//GetMesh->GetMaterial()->GetShader()->Link();
	}

	void Light::SetIntensity( float intensity )
	{
		m_intensity = intensity;
	}

	void Light::SetColor( Color& color )
	{
		m_color = color;
	}
}