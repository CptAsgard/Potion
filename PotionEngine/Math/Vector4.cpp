#include "Vector4.hpp"
#include "Matrix.hpp"

#include <math.h>

namespace Potion
{
	const Vector4 Vector4::Zero = Vector4();
	const Vector4 Vector4::One = Vector4( 1, 1, 1, 1 );

	Vector4::Vector4()
	{
		X = 0.0f;
		Y = 0.0f;
		Z = 0.0f;
		W = 0.0f;
	}

	Vector4::Vector4( float values )
		: X( values ), Y( values ), Z( values ), W( values )
	{

	}

	Vector4::Vector4( float x, float y, float z, float w )
		: X( x ), Y( y ), Z( z ), W( w )
	{

	}

	float Vector4::Distance( const Vector4& other ) const
	{
		return sqrtf( ((this->X - other.X) * (this->X - other.X)) + ((this->Y - other.Y) * (this->Y - other.Y)) + ((this->Z - other.Z) * (this->Z - other.Z)) + ((this->W - other.W) * (this->W - other.W)) );
	}

	float Vector4::Magnitude() const
	{
		return sqrtf( SquareMagnitude() );
	}

	float Vector4::SquareMagnitude() const
	{
		return powf( X, 2.0 ) + powf( Y, 2.0 ) + powf( Z, 2.0 ) + powf( W, 2.0 );
	}

	Vector4 Vector4::Normalized() const
	{
		return (*this) / Magnitude();
	}

	float Vector4::Dot( const Vector4& other ) const
	{
		return X * other.X + Y * other.Y + Z * other.Z + W * other.W;
	}

	Vector4 Vector4::operator- ( const Vector4& other ) const
	{
		return Vector4( X - other.X, Y - other.Y, Z - other.Z, W - other.W );
	}

	Vector4 Vector4::operator+ ( const Vector4& other ) const
	{
		return Vector4( X + other.X, Y + other.Y, Z + other.Z, W + other.W );
	}

	Vector4 Vector4::operator* ( const float& scale ) const
	{
		return Vector4( X * scale, Y * scale, Z * scale, W * scale );
	}

	Vector4 Vector4::operator/ ( const Vector4& other ) const
	{
		return Vector4( X / other.X, Y / other.Y, Z / other.Z, W / other.W );
	}

	Vector4 Vector4::operator/ ( const float& scale ) const
	{
		return Vector4( X / scale, Y / scale, Z / scale, W / scale );
	}

	Vector4& Vector4::operator-= ( const Vector4& other )
	{
		X = X - other.X;
		Y = Y - other.Y;
		Z = Z - other.Z;
		W = W - other.W;
		return *this;
	}

	Vector4& Vector4::operator+= ( const Vector4& other )
	{
		X = X + other.X;
		Y = Y + other.Y;
		Z = Z + other.Z;
		W = W + other.W;
		return *this;
	}

	Vector4& Vector4::operator*= ( const Vector4& other )
	{
		X = X * other.X;
		Y = Y * other.Y;
		Z = Z * other.Z;
		W = W * other.W;
		return *this;
	}

	Vector4& Vector4::operator*= ( const float& other )
	{
		X = X + other;
		Y = Y + other;
		Z = Z + other;
		W = W + other;
		return *this;
	}

	Vector4& Vector4::operator/= ( const Vector4& other )
	{
		X = X / other.X;
		Y = Y / other.Y;
		Z = Z / other.Z;
		W = W / other.W;
		return *this;
	}

	Vector4& Vector4::operator/= ( const float& other )
	{
		X = X / other;
		Y = Y / other;
		Z = Z / other;
		W = W / other;
		return *this;
	}

	Vector4 Vector4::operator-() const
	{
		return Vector4( -X, -Y, -Z, -W );
	}

	bool Vector4::operator== ( const Vector4& other ) const
	{
		return X == other.X && Y == other.Y && Z == other.Z && W == other.W;
	}

	bool Vector4::operator!= ( const Vector4& other ) const
	{
		return !operator==( other );
	}

	const Vector4 operator*( const Vector4& lhs, const Vector4& rhs )
	{
		return Vector4( lhs.X * rhs.X, lhs.Y * rhs.Y, lhs.Z * rhs.Z, lhs.W * rhs.W );
	}
}
