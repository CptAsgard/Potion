#pragma once
#ifndef _Vector4_H
#define _Vector4_H

namespace Potion
{
	class Vector4
	{
	public:
		float X, Y, Z, W;
		Vector4();
		Vector4( float values );
		Vector4( float x, float y, float z, float w );

		float Length() const;
		Vector4 Normalized() const;

		float Distance( const Vector4& other ) const;
		Vector4 Cross( const Vector4& other ) const;
		float Dot( const Vector4& other ) const;

		Vector4 operator- ( const Vector4& other ) const;
		Vector4 operator+ ( const Vector4& other ) const;
		Vector4 operator* ( const float& other ) const;
		Vector4 operator/ ( const Vector4& other ) const;
		Vector4 operator/ ( const float& other ) const;

		Vector4 operator- () const;

		Vector4& operator-= ( const Vector4& other );
		Vector4& operator+= ( const Vector4& other );
		Vector4& operator*= ( const Vector4& other );
		Vector4& operator*= ( const float& other );
		Vector4& operator/= ( const Vector4& other );
		Vector4& operator/= ( const float& other );

		bool operator== ( const Vector4& other ) const;
		bool operator!= ( const Vector4& other ) const;

		const static Vector4 Zero;
		const static Vector4 One;
	};
	const Vector4 operator*( const Vector4& lhs, const Vector4& rhs );
}

#endif // _Vector4_H
