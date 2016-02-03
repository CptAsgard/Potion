#include <stdint.h>
#include <GLFW\glfw3.h>

#pragma once
#ifndef _POT_UTIL
#define _POT_UTIL

#define MATH_PI (3.14159265358f)
#define MATH_PI_2 (MATH_PI/2)

#define POT_GET_TIME_MS ((float)(glfwGetTime() * 1000))

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

#endif // _POT_UTIL