#ifndef _LIGHT_H
#define _LIGHT_H

#include "Color.hpp"
#include "Transform.hpp"

#include "..\World\Entity.hpp"

namespace Potion
{
	class Light : public Entity
	{
	public:
		Light();

		void SetIntensity( float intensity );

		void SetColor( Color& color );

		void SetAttenuation( float attenuation );

		void SetAmbientValue( float ambient );

		void SetConeAngle( float angle );

	private:
		Color m_color;

		float m_intensity;
		float m_attenuation;
		float m_ambient;
		float m_coneAngle;

	};
}

#endif // _LIGHT_H