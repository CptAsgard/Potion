#ifndef _LIGHT_H
#define _LIGHT_H

#include "Color.hpp"
#include "Transform.hpp"

#include "..\World\GameObject.hpp"

namespace Potion
{
	class Light : public GameObject
	{
	public:
		Light();

		void SetIntensity( float intensity );
		void SetColor( Color& color );

	private:
		float m_intensity;
		Color m_color;

	};
}

#endif // _LIGHT_H