#include "Renderer.hpp"

using namespace Potion;

Potion::Renderer::Renderer( Material* material ) : material( material )
{
	projParam = material->GetShader()->GetParameter( "_View2Proj" );
	modelParam = material->GetShader()->GetParameter( "_Object2World" );
	viewParam = material->GetShader()->GetParameter( "_World2View" );

	cameraPosParam = material->GetShader()->GetParameter( "_WorldSpaceCameraPos" );

#ifndef USE_VERTEX_ARRAY_OBJECTS
	_positionAttrib = _material->GetShader()->GetAttribute( "position" );
	_normalAttrib = _material->GetShader()->GetAttribute( "normal" );
	_textureAttrib = _material->GetShader()->GetAttribute( "uv" );
#endif
}

void Renderer::Begin( const Matrix& view, const Matrix& projection )
{
	material->ActivateForDraw();

	projParam->SetValue( projection );
	viewParam->SetValue( view );
}

void Renderer::Render( const RenderDataPayload& payload )
{
	modelParam->SetValue( payload.matrix );

	// TODO: Camera position doesn't change between rendering. Move to Begin()
	cameraPosParam->SetValue( payload.camera->GetTransform().GetPosition() );

#ifdef USE_VERTEX_ARRAY_OBJECTS
	const GLuint vao = payload.mesh->GetVertexArray();

	glBindVertexArray( vao );
	GL_GET_ERROR();
#else
	const GLuint* vbo = payload.mesh->GetVertexBuffers();

	// Bind the buffers to the global state
	glBindBuffer( GL_ARRAY_BUFFER, vbo[ 0 ] );
	GL_GET_ERROR();
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vbo[ 1 ] );
	GL_GET_ERROR();

	// Default to VBO values, the pointer addresses are interpreted as byte-offsets.
	const void* firstPosition = reinterpret_cast<const void*>( offsetof( VertexFormat, Position ) );
	const void* firstNormal = reinterpret_cast<const void*>( offsetof( VertexFormat, Normal ) );
	const void* firstTexture = reinterpret_cast<const void*>( offsetof( VertexFormat, Texture ) );

	GLsizei size = sizeof( VertexFormat );
	_positionAttrib->SetAttributePointer( 3, GL_FLOAT, GL_FALSE, size, firstPosition );
	_normalAttrib->SetAttributePointer( 3, GL_FLOAT, GL_FALSE, size, firstNormal );
	_textureAttrib->SetAttributePointer( 2, GL_FLOAT, GL_FALSE, size, firstTexture );
#endif

	const void* firstIndex = reinterpret_cast<const void*>( 0 );
	glDrawElements( GL_TRIANGLES, payload.mesh->GetIndexCount(), GL_UNSIGNED_SHORT, firstIndex );
	GL_GET_ERROR();

#ifdef USE_VERTEX_ARRAY_OBJECTS
	glBindVertexArray( 0 );
	GL_GET_ERROR();
#else
	// Unbind buffers from global state.
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	GL_GET_ERROR();

	_positionAttrib->DisableAttributePointer();
	_normalAttrib->DisableAttributePointer();
	_textureAttrib->DisableAttributePointer();
#endif
}

void Renderer::End()
{
	material->GetShader()->Deactivate();
}