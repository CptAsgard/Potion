#include "Matrix.hpp"

#define _SCL_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <math.h>
#include <algorithm>

namespace Potion
{
	Matrix::Matrix()
	{
		const float newvals[] = { 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f };
		std::copy( newvals, newvals + sizeof( newvals ) / sizeof( newvals[ 0 ] ), values );
	}

	Matrix::Matrix( float value )
	{
		const float newvals[] = { value, value, value, value, value, value, value, value, value, value, value, value, value, value, value, value };
		std::copy( newvals, newvals + sizeof( newvals ) / sizeof( newvals[ 0 ] ), values );
	}

	Matrix::Matrix( float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44 )
	{
		const float newvals[] = { m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44 };
		std::copy( newvals, newvals + sizeof( newvals ) / sizeof( newvals[ 0 ] ), values );
	}

	Vector3 Matrix::operator*( const Vector3 & vec ) const
	{
		return TransformDirectionVector( vec );
	}

	Matrix Matrix::operator*( const Matrix& other ) const
	{
		Matrix retVal;

		retVal.values[ 0 ] = values[ 0 ] * other.values[ 0 ] + values[ 1 ] * other.values[ 4 ] + values[ 2 ] * other.values[ 8 ] + values[ 3 ] * other.values[ 12 ];
		retVal.values[ 1 ] = values[ 0 ] * other.values[ 1 ] + values[ 1 ] * other.values[ 5 ] + values[ 2 ] * other.values[ 9 ] + values[ 3 ] * other.values[ 13 ];
		retVal.values[ 2 ] = values[ 0 ] * other.values[ 2 ] + values[ 1 ] * other.values[ 6 ] + values[ 2 ] * other.values[ 10 ] + values[ 3 ] * other.values[ 14 ];
		retVal.values[ 3 ] = values[ 0 ] * other.values[ 3 ] + values[ 1 ] * other.values[ 7 ] + values[ 2 ] * other.values[ 11 ] + values[ 3 ] * other.values[ 15 ];

		retVal.values[ 4 ] = values[ 4 ] * other.values[ 0 ] + values[ 5 ] * other.values[ 4 ] + values[ 6 ] * other.values[ 8 ] + values[ 7 ] * other.values[ 12 ];
		retVal.values[ 5 ] = values[ 4 ] * other.values[ 1 ] + values[ 5 ] * other.values[ 5 ] + values[ 6 ] * other.values[ 9 ] + values[ 7 ] * other.values[ 13 ];
		retVal.values[ 6 ] = values[ 4 ] * other.values[ 2 ] + values[ 5 ] * other.values[ 6 ] + values[ 6 ] * other.values[ 10 ] + values[ 7 ] * other.values[ 14 ];
		retVal.values[ 7 ] = values[ 4 ] * other.values[ 3 ] + values[ 5 ] * other.values[ 7 ] + values[ 6 ] * other.values[ 11 ] + values[ 7 ] * other.values[ 15 ];

		retVal.values[ 8 ] = values[ 8 ] * other.values[ 0 ] + values[ 9 ] * other.values[ 4 ] + values[ 10 ] * other.values[ 8 ] + values[ 11 ] * other.values[ 12 ];
		retVal.values[ 9 ] = values[ 8 ] * other.values[ 1 ] + values[ 9 ] * other.values[ 5 ] + values[ 10 ] * other.values[ 9 ] + values[ 11 ] * other.values[ 13 ];
		retVal.values[ 10 ] = values[ 8 ] * other.values[ 2 ] + values[ 9 ] * other.values[ 6 ] + values[ 10 ] * other.values[ 10 ] + values[ 11 ] * other.values[ 14 ];
		retVal.values[ 11 ] = values[ 8 ] * other.values[ 3 ] + values[ 9 ] * other.values[ 7 ] + values[ 10 ] * other.values[ 11 ] + values[ 11 ] * other.values[ 15 ];

		retVal.values[ 12 ] = values[ 12 ] * other.values[ 0 ] + values[ 13 ] * other.values[ 4 ] + values[ 14 ] * other.values[ 8 ] + values[ 15 ] * other.values[ 12 ];
		retVal.values[ 13 ] = values[ 12 ] * other.values[ 1 ] + values[ 13 ] * other.values[ 5 ] + values[ 14 ] * other.values[ 9 ] + values[ 15 ] * other.values[ 13 ];
		retVal.values[ 14 ] = values[ 12 ] * other.values[ 2 ] + values[ 13 ] * other.values[ 6 ] + values[ 14 ] * other.values[ 10 ] + values[ 15 ] * other.values[ 14 ];
		retVal.values[ 15 ] = values[ 12 ] * other.values[ 3 ] + values[ 13 ] * other.values[ 7 ] + values[ 14 ] * other.values[ 11 ] + values[ 15 ] * other.values[ 15 ];

		return retVal;
	}

	Matrix Matrix::operator+( const Matrix & mat ) const
	{
		Matrix retVal;
		retVal.values[ 0 ] = values[ 0 ] + mat.values[ 0 ];
		retVal.values[ 1 ] = values[ 1 ] + mat.values[ 1 ];
		retVal.values[ 2 ] = values[ 2 ] + mat.values[ 2 ];
		retVal.values[ 3 ] = values[ 3 ] + mat.values[ 3 ];

		retVal.values[ 4 ] = values[ 4 ] + mat.values[ 4 ];
		retVal.values[ 5 ] = values[ 5 ] + mat.values[ 5 ];
		retVal.values[ 6 ] = values[ 6 ] + mat.values[ 6 ];
		retVal.values[ 7 ] = values[ 7 ] + mat.values[ 7 ];

		retVal.values[ 8 ] = values[ 8 ] + mat.values[ 8 ];
		retVal.values[ 9 ] = values[ 9 ] + mat.values[ 9 ];
		retVal.values[ 10 ] = values[ 10 ] + mat.values[ 10 ];
		retVal.values[ 11 ] = values[ 11 ] + mat.values[ 11 ];

		retVal.values[ 12 ] = values[ 12 ] + mat.values[ 12 ];
		retVal.values[ 13 ] = values[ 13 ] + mat.values[ 13 ];
		retVal.values[ 14 ] = values[ 14 ] + mat.values[ 14 ];
		retVal.values[ 15 ] = values[ 15 ] + mat.values[ 15 ];
		return retVal;
	}

	Matrix Matrix::operator-( const Matrix & mat ) const
	{
		Matrix retVal;
		retVal.values[ 0 ] = values[ 0 ] - mat.values[ 0 ];
		retVal.values[ 1 ] = values[ 1 ] - mat.values[ 1 ];
		retVal.values[ 2 ] = values[ 2 ] - mat.values[ 2 ];
		retVal.values[ 3 ] = values[ 3 ] - mat.values[ 3 ];

		retVal.values[ 4 ] = values[ 4 ] - mat.values[ 4 ];
		retVal.values[ 5 ] = values[ 5 ] - mat.values[ 5 ];
		retVal.values[ 6 ] = values[ 6 ] - mat.values[ 6 ];
		retVal.values[ 7 ] = values[ 7 ] - mat.values[ 7 ];

		retVal.values[ 8 ] = values[ 8 ] - mat.values[ 8 ];
		retVal.values[ 9 ] = values[ 9 ] - mat.values[ 9 ];
		retVal.values[ 10 ] = values[ 10 ] - mat.values[ 10 ];
		retVal.values[ 11 ] = values[ 11 ] - mat.values[ 11 ];

		retVal.values[ 12 ] = values[ 12 ] - mat.values[ 12 ];
		retVal.values[ 13 ] = values[ 13 ] - mat.values[ 13 ];
		retVal.values[ 14 ] = values[ 14 ] - mat.values[ 14 ];
		retVal.values[ 15 ] = values[ 15 ] - mat.values[ 15 ];
		return retVal;
	}

	/// TODO: Implement
	Matrix Matrix::CreateRotate( float angle, const Vector3 & axis )
	{
		return Matrix();
	}

	Matrix Matrix::CreateRotateX( float rotation )
	{
		Matrix retVal;
		retVal.values[ 5 ] = cos( rotation );
		retVal.values[ 6 ] = -sin( rotation );
		retVal.values[ 9 ] = sin( rotation );
		retVal.values[ 10 ] = cos( rotation );
		return retVal;
	}

	Matrix Matrix::CreateRotateY( float rotation )
	{
		Matrix retVal;
		retVal.values[ 0 ] = cos( rotation );
		retVal.values[ 2 ] = sin( rotation );
		retVal.values[ 8 ] = -sin( rotation );
		retVal.values[ 10 ] = cos( rotation );
		return retVal;
	}

	Matrix Matrix::CreateRotateZ( float rotation )
	{
		Matrix retVal;
		retVal.values[ 0 ] = cos( rotation );
		retVal.values[ 1 ] = -sin( rotation );
		retVal.values[ 4 ] = sin( rotation );
		retVal.values[ 5 ] = cos( rotation );
		return retVal;
	}

	Vector3 Matrix::TransformDirectionVector( const Vector3& direction ) const
	{
		Vector3 retVal = Vector3();
		retVal.X = direction.X * values[ 0 ] + direction.Y * values[ 1 ] + direction.Z * values[ 2 ] + values[ 3 ];
		retVal.Y = direction.X * values[ 4 ] + direction.Y * values[ 5 ] + direction.Z * values[ 6 ] + values[ 7 ];
		retVal.Z = direction.X * values[ 8 ] + direction.Y * values[ 9 ] + direction.Z * values[ 10 ] + values[ 11 ];
		return retVal;
	}

	Matrix Matrix::CreateScale( const Vector3 & scale )
	{
		Matrix retVal;
		retVal.values[ 0 ] = scale.X;
		retVal.values[ 5 ] = scale.Y;
		retVal.values[ 10 ] = scale.Z;
		return retVal;
	}

	Matrix Matrix::CreateTranslation( float x, float y, float z )
	{
		Matrix retVal;
		retVal.values[ 3 ] = x;
		retVal.values[ 7 ] = y;
		retVal.values[ 11 ] = z;
		return retVal;
	}

	Matrix Matrix::CreateTranslation( const Vector3& pos )
	{
		return CreateTranslation( pos.X, pos.Y, pos.Z );
	}

	Vector3 Matrix::GetTranslation() const
	{
		return this->TransformDirectionVector( Vector3::Zero );
	}

	void Matrix::SetTranslation( const Vector3 & vec )
	{
		values[ 3 ] = vec.X;
		values[ 7 ] = vec.Y;
		values[ 11 ] = vec.Z;
	}

	void Matrix::Invert()
	{
		float num1 = this->values[ 0 ];
		float num2 = this->values[ 1 ];
		float num3 = this->values[ 2 ];
		float num4 = this->values[ 3 ];
		float num5 = this->values[ 4 ];
		float num6 = this->values[ 5 ];
		float num7 = this->values[ 6 ];
		float num8 = this->values[ 7 ];
		float num9 = this->values[ 8 ];
		float num10 = this->values[ 9 ];
		float num11 = this->values[ 10 ];
		float num12 = this->values[ 11 ];
		float num13 = this->values[ 12 ];
		float num14 = this->values[ 13 ];
		float num15 = this->values[ 14 ];
		float num16 = this->values[ 15 ];

		float num17 = (num11 * num16 - num12 * num15);
		float num18 = (num10 * num16 - num12 * num14);
		float num19 = (num10 * num15 - num11 * num14);
		float num20 = (num9 * num16 - num12 * num13);
		float num21 = (num9 * num15 - num11 * num13);
		float num22 = (num9 * num14 - num10 * num13);
		float num23 = (num6 * num17 - num7 * num18 + num8 * num19);
		float num24 = -(num5 * num17 - num7 * num20 + num8 * num21);
		float num25 = (num5 * num18 - num6 * num20 + num8 * num22);
		float num26 = -(num5 * num19 - num6 * num21 + num7 * num22);
		float num27 = (1.0f / (num1 * num23 + num2 * num24 + num3 * num25 + num4 * num26));

		float num28 = (num7 * num16 - num8 * num15);
		float num29 = (num6 * num16 - num8 * num14);
		float num30 = (num6 * num15 - num7 * num14);
		float num31 = (num5 * num16 - num8 * num13);
		float num32 = (num5 * num15 - num7 * num13);
		float num33 = (num5 * num14 - num6 * num13);

		float num34 = (num7 * num12 - num8 * num11);
		float num35 = (num6 * num12 - num8 * num10);
		float num36 = (num6 * num11 - num7 * num10);
		float num37 = (num5 * num12 - num8 * num9);
		float num38 = (num5 * num11 - num7 * num9);
		float num39 = (num5 * num10 - num6 * num9);

		values[ 0 ] = num23 * num27;
		values[ 1 ] = -(num2 * num17 - num3 * num18 + num4 * num19) * num27;
		values[ 2 ] = (num2 * num28 - num3 * num29 + num4 * num30) * num27;
		values[ 3 ] = -(num2 * num34 - num3 * num35 + num4 * num36) * num27;
		values[ 4 ] = num24 * num27;
		values[ 5 ] = (num1 * num17 - num3 * num20 + num4 * num21) * num27;
		values[ 6 ] = -(num1 * num28 - num3 * num31 + num4 * num32) * num27;
		values[ 7 ] = (num1 * num34 - num3 * num37 + num4 * num38) * num27;
		values[ 8 ] = num25 * num27;
		values[ 9 ] = -(num1 * num18 - num2 * num20 + num4 * num22) * num27;
		values[ 10 ] = (num1 * num29 - num2 * num31 + num4 * num33) * num27;
		values[ 11 ] = -(num1 * num35 - num2 * num37 + num4 * num39) * num27;
		values[ 12 ] = num26 * num27;
		values[ 13 ] = (num1 * num19 - num2 * num21 + num3 * num22) * num27;
		values[ 14 ] = -(num1 * num30 - num2 * num32 + num3 * num33) * num27;
		values[ 15 ] = (num1 * num36 - num2 * num38 + num3 * num39) * num27;
	}

	void Matrix::Transpose()
	{
		for( int x = 0; x < 4; x++ )
		{
			for( int y = 0; y < 4; y++ )
			{
				this->values[ x * 4 + y ] = this->values[ y * 4 + x ];
			}
		}
	}

	/// TODO: Implement
	void Matrix::SetOrientation( const Vector3 & x, const Vector3 & y, const Vector3 & z )
	{}

	/// TODO: Implement
	void Matrix::SetEulerAxis( float yaw, float pitch, float roll )
	{}

	/// TODO: Implement
	Vector3 Matrix::GetXAxis() const
	{
		return Vector3();
	}

	/// TODO: Implement
	Vector3 Matrix::GetYAxis() const
	{
		return Vector3();
	}

	/// TODO: Implement
	Vector3 Matrix::GetZAxis() const
	{
		return Vector3();
	}

	/// TODO: Implement
	float Matrix::Determinant() const
	{
		return 0.0f;
	}

	/// TODO: Implement
	Matrix Matrix::CreateOrtho( float left, float right, float bottom, float top, float nearZ, float farZ )
	{
		return Matrix();
	}

	/// TOOD: Implement
	Matrix Matrix::CreateFrustum( float left, float right, float bottom, float top, float nearZ, float farZ )
	{
		return Matrix();
	}

	Matrix Matrix::CreateLookAt( const Vector3& eyePos, const Vector3& targetPos, const Vector3& upPos )
	{
		Vector3 dir = (eyePos - targetPos).Normalized();
		Vector3 right = upPos.Cross( dir ).Normalized();
		Vector3 up = dir.Cross( right ).Normalized();

		Matrix orientation = Matrix(
			right.X, right.Y, right.Z, 0,
			up.X, up.Y, up.Z, 0,
			dir.X, dir.Y, dir.Z, 0,
			0, 0, 0, 1
			);

		Matrix translation = Matrix(
			1, 0, 0, -eyePos.X,
			0, 1, 0, -eyePos.Y,
			0, 0, 1, -eyePos.Z,
			0, 0, 0, 1
			);

		// Combine the orientation and translation to compute the view matrix
		return (orientation * translation);
	}

	Matrix Matrix::CreatePerspective( float fovy, float aspect, float zNear, float zFar )
	{
		float f = float( tan( M_PI_2 - 0.5f * fovy ) );
		float rangeInv = 1.0f / (zNear - zFar);

		Matrix retVal( 0 );

		retVal.values[ 0 ] = f / aspect;
		retVal.values[ 5 ] = f;
		retVal.values[ 10 ] = (zNear + zFar) * rangeInv;
		retVal.values[ 11 ] = zNear * zFar * rangeInv * 2.0f;
		retVal.values[ 14 ] = -1.0;

		return retVal;
	}

	void Matrix::DebugPrint() const
	{
		printf( "Matrix object at %p\n", this );
		printf( "m11: %+f m12: %+f m13: %+f m14: %+f \n"
			"m21: %+f m22: %+f m23: %+f m24: %+f \n"
			"m31: %+f m32: %+f m33: %+f m34: %+f \n"
			"m41: %+f m42: %+f m43: %+f m44: %+f \n",
			values[ 0 ], values[ 1 ], values[ 2 ], values[ 3 ],
			values[ 4 ], values[ 5 ], values[ 6 ], values[ 7 ],
			values[ 8 ], values[ 9 ], values[ 10 ], values[ 11 ],
			values[ 12 ], values[ 13 ], values[ 14 ], values[ 15 ]
			);
	}
}
