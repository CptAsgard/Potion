#pragma once

#include "..\Math\Matrix.hpp"

#include "..\Rendering\Mesh.hpp"
#include "..\Rendering\Material.hpp"
#include "..\Rendering\Texture.hpp"

#include "..\World\Camera.hpp"

// For measuring the performance of using VAOs vs not using VAOs
#define USE_VERTEX_ARRAY_OBJECTS

namespace Potion
{
	// TODO: Need to copy data for possible future thread-safety?
	struct RenderDataPayload
	{
		Mesh* mesh;
		Material* material;
		Camera* camera;

		// Matrices aren't persistent but instead calculated when traversing the scene graph.
		Matrix matrix;

		RenderDataPayload( Mesh* _mesh, Material* _material, Matrix _matrix, Camera* _camera ) : 
			mesh( _mesh ), material( _material ), matrix( _matrix ), camera( _camera )
		{}
	};

	class Renderer
	{
	public:
		Renderer( Material* material );

		// Add lighting?
		void Begin( const Matrix& view, const Matrix& projection );

		void Render( const RenderDataPayload& payload );

		void End();

	protected:
		Material* material;
		
		ShaderParameter* projParam;
		ShaderParameter* modelParam;
		ShaderParameter* viewParam;
		ShaderParameter* cameraPosParam;

		ShaderParameter* textureParam;

#ifndef USE_VERTEX_ARRAY_OBJECTS
		ShaderAttribute* _positionAttrib;
		ShaderAttribute* _normalAttrib;
		ShaderAttribute* _textureAttrib;
#endif

		//shader->SetUniform( std::string( "_WorldSpaceCameraPos" ), camera->GetTransform().GetPosition() );
		//shader->SetUniform( std::string( "_Object2World" ), transform.GetLocalToWorldMatrix() );
		//shader->SetUniform( std::string( "_Normal2World" ), transform.GetLocalToWorldMatrix().Inverted().Mirror() );

		//shader->SetUniform( std::string( "_Color" ), material->GetColor().AsRGB() );
		//shader->SetUniform( std::string( "_SpecularColor" ), material->GetSpecularColor().AsRGB() );
		//shader->SetUniform( std::string( "_Shininess" ), material->GetShininess() );
	};

}