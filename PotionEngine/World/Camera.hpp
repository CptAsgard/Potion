#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H

#include "..\Math\Matrix.hpp"

#include "..\World\GameObject.hpp"
#include "..\Systems\UniqueID.hpp"

#include "..\Rendering\TextureCube.hpp"
#include "..\Rendering\TextureRender.hpp"

namespace Potion
{
	// TODO: Camera culling mask
	class Camera : public GameObject
	{
	public:
		Camera( float fovy, float aspectRatio, float zNear, float zFar );
		virtual ~Camera();

		void StartDraw();

		void EndDraw();

		uint8_t GetCameraID() const;

		bool IsCulled( uint32_t layer ) const;

		void SetSkybox( TextureCube* cubemap );

		void SetRenderTarget( TextureRender* textureRender );

		Matrix* GetProjectionMatrix();
		Matrix* GetViewMatrix();

	protected:
		virtual void Initialize( SceneManager * game ) = 0;

		virtual void Update( SceneManager * game, float deltaTime ) = 0;

		Model skyBox;
		TextureCube* skyboxTex;

		Model renderTarget;
		TextureRender* renderTargetTex;

		static UniqueID uniqueID;
		uint8_t cameraID;

		Matrix projectionMatrix;
		Matrix viewMatrix;

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