#include <stdint.h>
#include <GLFW\glfw3.h>

#pragma once
#ifndef _POT_UTIL
#define _POT_UTIL

#define MATH_PI (3.14159265358f)
#define MATH_PI_2 (MATH_PI/2)

#define POT_GET_TIME_MS ((float)(glfwGetTime() * 1000))

#define POT_KEY_PRESS 1
#define POT_KEY_HOLD 2
#define POT_KEY_RELEASED 0
#define POT_KEY_UP 3

#ifdef _DEBUG
#ifdef _MSC_VER
#define asmBreak __asm{int 3}
#else
#define asmBreak __asm("int $3")
#endif

#define POT_ASSERT(test) {if(!(test)) { printf("Assertion failed in file %s, on line %i\n", __FILE__, __LINE__); asmBreak; }}

#ifndef assert
#define assert(test) {if(!(test)) printf("Assertion failed in file %s, on line %i\n", __FILE__, __LINE__);}
#endif

#ifndef ASSERT
#define ASSERT(test) {if(!(test)) printf("Assertion failed in file %s, on line %i\n", __FILE__, __LINE__);}
#endif

#ifndef checkGL
#define checkGL {int ret = glGetError(); if(ret != 0) {printf("GL failed in file %s, on line %i: err: %d, %s\n", __FILE__, __LINE__, ret, gluErrorString(ret)); }}
#endif

#else

#define POT_ASSERT(test)

#ifndef assert
#define assert(test)
#endif

#ifndef ASSERT
#define ASSERT(test)
#endif

#ifndef asmBreak
#define asmBreak
#endif

#ifndef checkGL
#define checkGL
#endif

#endif

namespace Potion
{
	template<typename T>
	inline T DegToRad( T deg )
	{
		return deg * T( MATH_PI / 180 );
	}

	template<typename T>
	inline T RadToDeg( T rad )
	{
		return rad * T( 180 / MATH_PI );
	}

	// Layer flags, 0 .. 31
	enum Layer
	{
		Default = 0,
		TransparentFX = 1,
		UI = 2
	};
}
#endif // _POT_UTIL