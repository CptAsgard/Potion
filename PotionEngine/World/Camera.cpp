#include "Camera.hpp"

#include "..\Util.hpp"

namespace Potion
{
	Camera::Camera( float fovy, float aspectRatio, float zNear, float zFar )
	{
		Event.Send( CameraCreatedMessage( this ) );

		m_projectionMatrix = Matrix::CreatePerspective( DegToRad(fovy), aspectRatio, zNear, zFar );
	}

	Camera::~Camera()
	{
		Event.Send( CameraDestroyedMessage( this ) );
	}

	void Camera::Render( GameObject & go )
	{
		go.GetMesh()->GLDraw( TransformModelMatrixToMVP( go.GetTransform().GetLocalToWorldMatrix() ) );
	}

	const Matrix Camera::TransformModelMatrixToMVP( const Matrix & model )
	{
		m_viewMatrix = Matrix::CreateLookAt( GetTransform().GetPosition(), GetTransform().GetPosition() + GetTransform().GetForward(), Vector3( 0, 1, 0 ) );
		Vector3 forward = GetTransform().GetForward();
		return m_projectionMatrix * m_viewMatrix * model;
	}
}