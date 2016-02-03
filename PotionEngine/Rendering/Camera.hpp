#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H

#include "..\Math\Matrix.hpp"
#include "Transform.hpp"
#include "Mesh.hpp"

namespace Potion
{
	class Camera
	{
	public:
		Camera( float fovy, float aspectRatio, float zNear, float zFar );

		// Get MVP from your Model matrix
		const Matrix Camera::TransformModelMatrixToMVP( const Matrix& model );

		void LookAt( Vector3 pos );

		void Render( Mesh& drawable );

		Transform transform;

	private:
		Matrix m_matrix;

	};
}

#endif // _CAMERA_H