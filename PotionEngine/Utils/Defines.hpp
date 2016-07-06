#pragma once

#include <cmath>
#include "..\Math\Vector3.hpp"

// Define the ASSERT and DEBUG macros
#ifdef _WIN32
#define ASSERT _ASSERT
#ifdef _DEBUG 
#define DEBUG
#endif
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

namespace Potion
{
	#define KEY_PRESS 1
	#define KEY_HOLD 2
	#define KEY_RELEASED 0
	#define KEY_UP 3

	// Layer flags, 0 .. 31
	enum Layer
	{
		Default = 0,
		TransparentFX = 1 << 0,
		UI = 1 << 1
		// 1 << 2
		// 1 << 3
		// etc.
	};

	typedef uint32_t ID;

	typedef unsigned int uint;
	typedef unsigned long ulong;
	typedef unsigned short ushort;
	typedef unsigned char uchar;

	const float Pi = 3.1415926535897932384626433832795f;
	const float TwoPi = Pi * 2;
	const float HalfPi = Pi / 2;
	const float QuarterPi = Pi / 4;

	inline float RadToDeg( float rad )	{ return rad * 180.0f / Pi; };
	inline float DegToRad( float deg )	{ return deg * Pi / 180.0f; }
	inline Vector3 RadToDeg( Vector3 rad ) { return rad * 180.0f / Pi; };
	inline Vector3 DegToRad( Vector3 deg ) { return deg * Pi / 180.0f; }

	/// Returns a random float between zero and 1
	inline float RandFloat() { return static_cast<float>( ( rand() ) / ( RAND_MAX + 1.0 ) ); }

	/// Returns a random float between x and y
	inline float RandInRange( float x, float y ) { return x + RandFloat()*( y - x ); }

	/// Returns a random int between from and to
	inline int RandInRange( int from, int to ) { return from + rand() % ( to - from ); }

	template <class T>
	inline T Modulo( T x, T m ) { return ( x % m + m ) % m; }

	template <class T>
	T Lerp( T a, T b, float t )
	{
		if( t < 0 )
			t = 0;
		else if( t > 1 )
			t = 1;
		//
		return a * ( 1.0f - t ) + b * t;
	}


#ifdef DEBUG

#define LOG(macro_format, ...)										\
{																	\
	printf(macro_format, ##__VA_ARGS__);							\
	const size_t macro_len = strlen(macro_format);					\
	if(macro_len > 0 && macro_format[macro_len - 1] != '\n')		\
	{																\
		printf("\n");												\
	}																\
}

#else
#define LOG(...) { }
#endif

}