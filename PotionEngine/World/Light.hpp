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

		float GetIntensity() const;
		void SetIntensity( float intensity );

		const Color& GetColor() const;
		void SetColor( Color& color );

		float GetAttenuation() const;
		void SetAttenuation( float attenuation );

		float GetConeAngle() const;
		void SetConeAngle( float angle );

		bool IsDirectional() const;
		void SetDirectional( bool flag );

	private:
		Color m_color;

		float m_intensity;
		float m_attenuation;
		float m_coneAngle;

		bool m_isDirectional;

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