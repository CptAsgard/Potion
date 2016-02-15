#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H

#include "..\Math\Matrix.hpp"

#include "..\World\GameObject.hpp"

namespace Potion
{
	class Camera : public GameObject
	{
	public:
		Camera( float fovy, float aspectRatio, float zNear, float zFar );

		~Camera();

		void Render( GameObject & go );

		// Get MVP from your Model matrix
		const Matrix Camera::TransformModelMatrixToMVP( const Matrix& model );

	private:
		Matrix m_projectionMatrix;
		Matrix m_viewMatrix;

	};

	struct CameraCreatedMessage
	{
		CameraCreatedMessage( Camera* ptr ) : newObj( ptr ) {}

		Camera* newObj;
	};
	struct CameraDestroyedMessage
	{
		CameraDestroyedMessage( Camera* ptr ) : newObj( ptr ) {}

		Camera* newObj;
	};
}

#endif // _CAMERA_H