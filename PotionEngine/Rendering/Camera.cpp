#include "Camera.hpp"

#include "..\Util.hpp"

namespace Potion
{
	Camera::Camera( float fovy, float aspectRatio, float zNear, float zFar )
	{
		m_projectionMatrix = Matrix::CreatePerspective( DegToRad(fovy), aspectRatio, zNear, zFar );
	}

	void Camera::Update( float deltaTime )
	{
		
	}

	void Camera::Render( Mesh & drawable )
	{
		drawable.Draw( TransformModelMatrixToMVP( drawable.transform.GetLocalToWorldMatrix() ) );
	}

	const Matrix Camera::TransformModelMatrixToMVP( const Matrix & model )
	{
		m_viewMatrix = Matrix::CreateLookAt( transform.GetPosition(), transform.GetPosition() + transform.GetForward(), Vector3( 0, 1, 0 ) );
		Vector3 forward = transform.GetForward();
		return m_projectionMatrix * m_viewMatrix * model;
	}
}