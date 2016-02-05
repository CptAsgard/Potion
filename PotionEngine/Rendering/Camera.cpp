#include "Camera.hpp"

#include "..\Util.hpp"

namespace Potion
{
	Camera::Camera( float fovy, float aspectRatio, float zNear, float zFar )
	{
		m_matrix = Matrix::CreatePerspective( DegToRad(fovy), aspectRatio, zNear, zFar );
	}

	void Camera::Render( Mesh & drawable )
	{
		drawable.Draw( TransformModelMatrixToMVP( drawable.transform.GetLocalToWorldMatrix() ) );
	}

	const Matrix Camera::TransformModelMatrixToMVP( const Matrix & model )
	{
		return m_matrix * transform.GetLocalToWorldMatrix() * model;
	}
}