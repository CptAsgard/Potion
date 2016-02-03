#include "Camera.hpp"

#include "..\Util.hpp"

namespace Potion
{
	Camera::Camera( float fovy, float aspectRatio, float zNear, float zFar )
	{
		m_matrix = Matrix::CreatePerspective( DegToRad(fovy), aspectRatio, zNear, zFar );
	}

	const Matrix Camera::TransformModelMatrixToMVP( const Matrix & model )
	{
		return m_matrix * transform.GetLocalToWorldMatrix() * model;
	}

	void Camera::LookAt( Vector3 pos )
	{
		transform.SetWorldMatrix( Matrix::CreateLookAt( transform.GetPosition(), pos, Vector3( 0.f, 1.f, 0.f ) ) );
	}

	void Camera::Render( Mesh & drawable )
	{
		drawable.Draw( TransformModelMatrixToMVP( drawable.transform.GetLocalToWorldMatrix() ) );
	}
}