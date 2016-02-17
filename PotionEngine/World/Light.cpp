#include "Light.hpp"

namespace Potion
{
	Light::Light() : m_isDirectional( false ), m_color( Color( 255.f, 255.f, 255.f ) ), m_intensity( 1.f )
	{
		Event.Send( LightCreatedMessage( this ) );
	}

	Light::~Light()
	{
		Event.Send( LightDestroyedMessage( this ) );
	}

	float Light::GetIntensity() const
	{
		return m_intensity;
	}

	void Light::SetIntensity( float intensity )
	{
		m_intensity = intensity;
	}

	const Color & Light::GetColor() const
	{
		return m_color;
	}

	void Light::SetColor( Color& color )
	{
		m_color = color;
	}

	float Light::GetAttenuation() const
	{
		return m_attenuation;
	}

	void Light::SetAttenuation( float attenuation )
	{
		m_attenuation = attenuation;
	}
	
	float Light::GetConeAngle() const
	{
		return m_coneAngle;
	}

	void Light::SetConeAngle( float angle )
	{
		m_coneAngle = angle;
	}

	bool Light::IsDirectional() const
	{
		return m_isDirectional;
	}

	void Light::SetDirectional( bool flag )
	{
		m_isDirectional = flag;
	}
}