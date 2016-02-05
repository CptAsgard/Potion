#include "Window.hpp"

#include "..\Util.hpp"

namespace Potion
{
	Window* Window::m_currentWindow = nullptr;

	void Window::OnKey( GLFWwindow* window, int key, int scancode, int action, int mods )
	{
		if( key < 0 || key > GLFW_KEY_LAST ) return; // filter out hardware that wants to be special and has special keys.
		if( m_currentWindow == nullptr ) return;

		if( action == GLFW_REPEAT ) return;

		m_currentWindow->SetKeyState( key, action );
	}

	void Window::OnMouse( GLFWwindow* window, int button, int action, int mods )
	{
		if( button < 0 || button > GLFW_MOUSE_BUTTON_LAST ) return; // filter out hardware that wants to be special and has special keys.
		if( m_currentWindow == nullptr ) return;

		m_currentWindow->SetMouseState( button, action );
	}

	void Window::OnChar( GLFWwindow* window, unsigned int ch )
	{

	}

	void Window::OnScroll( GLFWwindow* window, double sx, double sy )
	{

	}

	void Window::OnMousePos( GLFWwindow* window, double x, double y )
	{

	}

	void Window::OnFocus( GLFWwindow* window, int focus )
	{

	}

	Vector2 Window::GetMousePosition() const
	{
		double mouseX, mouseY;
		glfwGetCursorPos( this->m_handle, &mouseX, &mouseY );

		return Vector2( (float) mouseX, (float) mouseY );
	}

	void Window::SetMouse( int x, int y )
	{
	
	}

	void Window::SetMouse( const Vector2 & pos )
	{
	
	}

	void Window::ShouldCaptureMouse( bool capture )
	{
		if( capture )
			glfwSetInputMode( this->m_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
		else
			glfwSetInputMode( this->m_handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL );
	}

	void Window::SetKeyState( int key, int action )
	{
		this->m_keysIn[ key ] = action;
	}

	void Window::SetMouseState( int key, int action )
	{
		this->m_mouseIn[ key ] = action;
	}

	bool Window::GetKey( int key )
	{
		if( key < 0 || key > GLFW_KEY_LAST ) return false;
		return this->m_keysIn[ key ] == POT_KEY_PRESS || this->m_keysIn[ key ] == POT_KEY_HOLD;
	}

	bool Window::GetKeyDown( int key )
	{
		if( key < 0 || key > GLFW_KEY_LAST ) return false;
		return this->m_keysIn[ key ] == POT_KEY_PRESS;
	}

	bool Window::GetKeyUp( int key )
	{
		if( key < 0 || key > GLFW_KEY_LAST ) return false;
		return this->m_keysIn[ key ] == POT_KEY_RELEASED;
	}

	void Window::SetCallbacks() const
	{
		glfwSetKeyCallback( this->m_handle, this->OnKey );
		glfwSetMouseButtonCallback( this->m_handle, this->OnMouse );
		glfwSetScrollCallback( this->m_handle, this->OnScroll );
		glfwSetCharCallback( this->m_handle, this->OnChar );
		glfwSetCursorPosCallback( this->m_handle, this->OnMousePos );
		glfwSetWindowFocusCallback( this->m_handle, this->OnFocus );
	}

	void Window::UpdateKeyHolding()
	{
		for( int i = 0; i < GLFW_KEY_LAST; i++ ) {
			if( this->m_keysIn[ i ] == POT_KEY_PRESS ) {
				this->m_keysIn[ i ] = POT_KEY_HOLD;
			}

			if( this->m_keysIn[ i ] == POT_KEY_RELEASED ) {
				this->m_keysIn[ i ] = POT_KEY_UP;
			}
		}

		for( int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++ ) {
			if( this->m_mouseIn[ i ] == POT_KEY_PRESS ) {
				this->m_mouseIn[ i ] = POT_KEY_HOLD;
			}

			if( this->m_mouseIn[ i ] == POT_KEY_RELEASED ) {
				this->m_mouseIn[ i ] = POT_KEY_UP;
			}
		}
	}

	Window::Window()
	{
		this->m_handle = nullptr;
		
		memset( this->m_keysIn, POT_KEY_UP, GLFW_KEY_LAST );
		memset( this->m_mouseIn, POT_KEY_UP, GLFW_MOUSE_BUTTON_LAST );

		if( this->m_currentWindow == nullptr ) {
			this->m_currentWindow = this;
		}
	}

	Window::~Window()
	{
		glfwDestroyWindow( this->m_handle );
		glfwTerminate();
	}

	void error_callback( int error, const char* description )
	{
		printf( "GLFW error %d: '%s'\n", error, description );
	}

	void Window::SetTitle( std::string title )
	{
		glfwSetWindowTitle( this->m_handle, title.c_str() );
	}

	void Window::Close() const
	{
		glfwSetWindowShouldClose( this->m_handle, GL_TRUE );
	}

	bool Window::IsClosing() const
	{
		return (glfwWindowShouldClose( this->m_handle ) ? true : false);
	}

	Vector2 Window::GetSize() const
	{
		int x, y;

		glfwGetWindowSize( this->m_handle, &x, &y );
		return Vector2( x, y );
	}

	void Window::SwapBuffer() const
	{
		glfwSwapBuffers( this->m_handle );
	}

	void Window::PollEvents() const
	{
		glfwPollEvents();
	}

	bool Window::Create( const std::string& title, unsigned int width, unsigned int height )
	{
		/*****/
		/* GLFW Initialization
		/*****/

		if( glfwInit() != GL_TRUE ) {
			std::cout << "GLFW could not initialize!\n";
			return false;
		}

		glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
		glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
		glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

		glfwSetErrorCallback( error_callback );

		this->m_handle = glfwCreateWindow( (int) width, (int) height, title.c_str(), nullptr, nullptr );
		if( this->m_handle == nullptr ) {
			std::cout << "Failed to create GLFW window!\n";
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent( this->m_handle );

		this->SetCallbacks();

		/****** END *******/

		/*****/
		/* GLEW Initialization
		/*****/

		glewExperimental = GL_TRUE;
		if( glewInit() != GLEW_OK ) {
			std::cout << "Failed to initialize GLEW!\n";
			return false;
		}

		GLenum currentError = glGetError(); // Glew always throws a silly error, this is to filter that.
		if( !(currentError == GL_NO_ERROR || currentError == GL_INVALID_ENUM) ) {
			printf( "something's wrong with glew...%x\n", currentError );
			return false;
		}

		/****** END *******/

		glEnable( GL_DEPTH_TEST );

		glViewport( 0, 0, (GLsizei) width, (GLsizei) height );

		glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		return true;
	}
}