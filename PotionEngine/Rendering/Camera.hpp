#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H

#include "Transform.hpp"
#include "Mesh.hpp"

#include "..\Math\Matrix.hpp"

#include "..\World\MeshEntity.hpp"

namespace Potion
{
	class MeshEntity;

	class Camera
	{
	public:
		Camera( float fovy, float aspectRatio, float zNear, float zFar );

		void Render( MeshEntity & MeshEntity );

		// Get MVP from your Model matrix
		const Matrix Camera::TransformModelMatrixToMVP( const Matrix& model );

		Transform transform;

	private:
		Matrix m_projectionMatrix;
		Matrix m_viewMatrix;

	};
}

#endif // _CAMERA_H