#include "Light.hpp"

namespace Potion
{
	Light::Light()
	{
		Event.Send( LightCreatedMessage( this ) );
	}

	Light::~Light()
	{
		Event.Send( LightDestroyedMessage( this ) );
	}

	void Light::SetIntensity( float intensity )
	{
		m_intensity = intensity;
	}

	void Light::SetColor( Color& color )
	{
		m_color = color;
	}

	// TODO: Implement
	void Light::SetAttenuation( float attenuation )
	{
	
	}

	// TODO: Implement
	void Light::SetAmbientValue( float ambient )
	{
	
	}
	
	// TODO: Implement
	void Light::SetConeAngle( float angle )
	{
	
	}
}