#include "Light.hpp"

namespace Potion
{
	Light::Light() : isDirectional( false ), color( Color( 255, 255, 255 ) ), intensity( 1.f )
	{
		Event.Send( LightCreatedMessage( this ) );
	}

	Light::~Light()
	{
		Event.Send( LightDestroyedMessage( this ) );
	}

	float Light::GetIntensity() const
	{
		return intensity;
	}

	void Light::SetIntensity( float intensity )
	{
		this->intensity = intensity;
	}

	const Color & Light::GetColor() const
	{
		return color;
	}

	void Light::SetColor( Color& color )
	{
		this->color = color;
	}

	float Light::GetAttenuation() const
	{
		return attenuation;
	}

	void Light::SetAttenuation( float attenuation )
	{
		this->attenuation = attenuation;
	}
	
	float Light::GetConeAngle() const
	{
		return coneAngle;
	}

	void Light::SetConeAngle( float angle )
	{
		coneAngle = angle;
	}

	bool Light::IsDirectional() const
	{
		return isDirectional;
	}

	void Light::SetDirectional( bool flag )
	{
		isDirectional = flag;
	}
}