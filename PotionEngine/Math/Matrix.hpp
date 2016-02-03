#pragma once
#ifndef _MATRIX_H
#define _MATRIX_H

#include "Vector3.hpp"
#include "Vector2.hpp"

namespace Potion
{
	class Matrix
	{
	public:
		static Matrix CreateRotationX( float rotation );
		static Matrix CreateRotationY( float rotation );
		static Matrix CreateRotationZ( float rotation );
		static Matrix CreateScale( float scale );
		static Matrix CreateScale( float scaleX, float scaleY, float scaleZ );
		static Matrix CreateTranslation( float x, float y, float z );
		static Matrix CreateTranslation( const Vector3& pos );
		static Matrix CreateLookAt( float eyex, float eyey, float eyez, float targetx, float targety, float targetz, float upx, float upy, float upz );
		static Matrix CreateLookAt( const Vector3& eyePos, const Vector3& targetPos, const Vector3& up );
		static Matrix CreatePerspective( float fovy, float aspect, float zNear, float zFar );
		static Matrix CreateTRS( Vector3 pos, Vector3 rotation, Vector3 scale );

		~Matrix();
		Matrix();
		Matrix( float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44 );
		Matrix( float values );

		Matrix( const Matrix& other );
		Matrix( Matrix&& other );

		Matrix& operator= ( const Matrix& rhs );

		void DebugPrint() const;

		// Getting rotation and scale is nigh impossible.
		// Look into Matrix Decomposition/Singular Value Decomposition
		void SetPosition( const Vector3& input );
		void SetRotation( const Vector3& input );
		void SetScale( const Vector3& input );

		Vector3 TransformVector( float x, float y, float z ) const;
		Vector3 TransformVector( const Vector3& input ) const;

		Vector2 TransformVector( float x, float y ) const;
		Vector2 TransformVector( const Vector2& input ) const;

		Matrix Lerp( const Matrix& other, float timestep );
		Matrix Inverted();

		// to switch between column and row type
		Matrix Mirror();

		Matrix operator*( const Matrix& other ) const;
		void operator*=( const Matrix& other ) { *this = *this * other; }

		float* values;
	};
}

#endif // _MATRIX_H
