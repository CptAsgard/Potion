#ifndef _LIGHT_H
#define _LIGHT_H

#include "..\World\GameObject.hpp"

#include "..\Rendering\Color.hpp"

namespace Potion
{
	class Light : public GameObject
	{
	public:
		Light();
		~Light();

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

	struct LightCreatedMessage
	{
		LightCreatedMessage( Light* ptr ) : newObj( ptr ) {}

		Light* newObj;
	};
	struct LightDestroyedMessage
	{
		LightDestroyedMessage( Light* ptr ) : newObj( ptr ) {}

		Light* newObj;
	};
}

#endif // _LIGHT_H