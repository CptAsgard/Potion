#include "Light.hpp"

namespace Potion
{
	Light::Light() : GameObject()
	{
		mesh.GetMaterial()->SetShader( new Shader() );
		mesh.GetMaterial()->GetShader()->Attach( "../Resources/Shaders/lightObject.frag", GL_FRAGMENT_SHADER );
		mesh.GetMaterial()->GetShader()->Attach( "../Resources/Shaders/lightObject.vert", GL_VERTEX_SHADER );
		mesh.GetMaterial()->GetShader()->Link();
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