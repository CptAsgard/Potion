#include "Camera.hpp"

#include "..\Utils\Utils.hpp"
#include "..\Systems\Renderer.hpp"

namespace Potion
{
	UniqueID Camera::uniqueID;

	Camera::Camera( float fovy, float aspectRatio, float zNear, float zFar ) : skyBox( "Assets/box/Box.obj", new Material() ), renderTarget( "Assets/quad/Quad.obj", new Material() )
	{
		Event.Send( CameraCreatedMessage( this ) );

		projectionMatrix = Matrix::CreatePerspective( DegToRad( fovy ), aspectRatio, zNear, zFar );

		this->cameraID = Camera::uniqueID.GetNext();

		// TODO: Not generic behaviour. Shouldn't be in Camera
		skyBox.m_materials[ 0 ] = new Material();
		skyBox.m_materials[ 0 ]->SetShader( new Shader( "Assets/SkyBox.vsh", "Assets/SkyBox.fsh" ) );
		skyboxTex = nullptr;

		// TODO: Not generic behaviour. Shouldn't be in Camera
		renderTarget.m_materials[ 0 ] = new Material();
		renderTarget.m_materials[ 0 ]->SetShader( new Shader( "Assets/ImageEffect.vsh", "Assets/ImageEffect.fsh" ) );
		renderTargetTex = nullptr;

	}

	Camera::~Camera()
	{
		Event.Send( CameraDestroyedMessage( this ) );
		Camera::uniqueID.Free( this->cameraID );
	}

	void Camera::StartDraw()
	{
		// Draw everything as wireframe
		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

		if( renderTargetTex != nullptr )
			renderTargetTex->SetBufferActive();

		glClearColor( 154.f / 255.f, 206.f / 255.f, 235.f / 255.f, 1 );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glEnable( GL_DEPTH_TEST );
	}

	void Camera::EndDraw()
	{
		/// SKYBOX
		if( skyboxTex != nullptr )
		{
			glDepthFunc( GL_LEQUAL );

			Renderer renderer( skyBox.m_materials[ 0 ] );
			renderer.Begin( *GetViewMatrix(), *GetProjectionMatrix() );

			RenderDataPayload payload = RenderDataPayload(
				skyBox.m_meshes[ 0 ],
				skyBox.m_materials[ 0 ],
				Matrix(),
				this );

			renderer.Render( payload );

			renderer.End();

			glDepthFunc( GL_LESS );
		}



		/// RENDER TARGET
		if( renderTargetTex != nullptr )
		{
			renderTargetTex->SetBufferInactive();

			glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
			glClear( GL_COLOR_BUFFER_BIT );
			glDisable( GL_DEPTH_TEST );

			// TODO: Effects stack

			Renderer renderer( renderTarget.m_materials[ 0 ] );
			renderer.Begin( *GetViewMatrix(), *GetProjectionMatrix() );

			RenderDataPayload payload = RenderDataPayload(
				renderTarget.m_meshes[ 0 ],
				renderTarget.m_materials[ 0 ],
				Matrix(),
				this );

			renderer.Render( payload );

			renderer.End();
		}
	}

	uint8_t Camera::GetCameraID() const
	{
		return this->cameraID;
	}

	// TODO: bool IsCulled( int layer ) // checks if layer is culled or not
	bool Camera::IsCulled( uint32_t layer ) const
	{
		return false;
	}

	void Camera::SetSkybox( TextureCube * cubemap )
	{
		this->skyboxTex = cubemap;
		skyBox.m_materials[ 0 ]->SetTexture( "_Skybox", skyboxTex );
	}

	void Camera::SetRenderTarget( TextureRender * textureRender )
	{
		this->renderTargetTex = textureRender;
		renderTarget.m_materials[ 0 ]->SetTexture( "u_screenTexture", renderTargetTex );
	}

	Matrix * Camera::GetProjectionMatrix()
	{
		return &projectionMatrix;
	}

	Matrix * Camera::GetViewMatrix()
	{
		viewMatrix = Matrix::CreateLookAt( GetTransform().GetPosition(), GetTransform().GetPosition() + GetTransform().GetForward(), Vector3( 0, 1, 0 ) );
		return &viewMatrix;
	}
}