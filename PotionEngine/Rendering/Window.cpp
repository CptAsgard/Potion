#include "Window.hpp"

#include "..\Utils\Utils.hpp"

namespace Potion
{
	Window* Window::currentWindow = nullptr;

	void Window::OnKey( GLFWwindow* window, int key, int scancode, int action, int mods )
	{
		if( key < 0 || key > GLFW_KEY_LAST ) return; // filter out hardware that wants to be special and has special keys.
		if( currentWindow == nullptr ) return;

		if( action == GLFW_REPEAT ) return;

		currentWindow->SetKeyState( key, action );
	}

	void Window::OnMouse( GLFWwindow* window, int button, int action, int mods )
	{
		if( button < 0 || button > GLFW_MOUSE_BUTTON_LAST ) return; // filter out hardware that wants to be special and has special keys.
		if( currentWindow == nullptr ) return;

		currentWindow->SetMouseState( button, action );
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
		glfwGetCursorPos( this->handle, &mouseX, &mouseY );

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
			glfwSetInputMode( this->handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
		else
			glfwSetInputMode( this->handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL );
	}

	void Window::SetKeyState( int key, int action )
	{
		this->keysIn[ key ] = action;
	}

	void Window::SetMouseState( int key, int action )
	{
		this->mouseIn[ key ] = action;
	}

	bool Window::GetKey( int key )
	{
		if( key < 0 || key > GLFW_KEY_LAST ) return false;
		return this->keysIn[ key ] == KEY_PRESS || this->keysIn[ key ] == KEY_HOLD;
	}

	bool Window::GetKeyDown( int key )
	{
		if( key < 0 || key > GLFW_KEY_LAST ) return false;
		return this->keysIn[ key ] == KEY_PRESS;
	}

	bool Window::GetKeyUp( int key )
	{
		if( key < 0 || key > GLFW_KEY_LAST ) return false;
		return this->keysIn[ key ] == KEY_RELEASED;
	}

	void Window::SetCallbacks() const
	{
		glfwSetKeyCallback( this->handle, this->OnKey );
		glfwSetMouseButtonCallback( this->handle, this->OnMouse );
		glfwSetScrollCallback( this->handle, this->OnScroll );
		glfwSetCharCallback( this->handle, this->OnChar );
		glfwSetCursorPosCallback( this->handle, this->OnMousePos );
		glfwSetWindowFocusCallback( this->handle, this->OnFocus );
	}

	void Window::UpdateKeyHolding()
	{
		for( int i = 0; i < GLFW_KEY_LAST; i++ )
		{
			if( this->keysIn[ i ] == KEY_PRESS )
			{
				this->keysIn[ i ] = KEY_HOLD;
			}

			if( this->keysIn[ i ] == KEY_RELEASED )
			{
				this->keysIn[ i ] = KEY_UP;
			}
		}

		for( int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++ )
		{
			if( this->mouseIn[ i ] == KEY_PRESS )
			{
				this->mouseIn[ i ] = KEY_HOLD;
			}

			if( this->mouseIn[ i ] == KEY_RELEASED )
			{
				this->mouseIn[ i ] = KEY_UP;
			}
		}
	}

	Window::Window()
	{
		this->handle = nullptr;

		memset( this->keysIn, KEY_UP, GLFW_KEY_LAST );
		memset( this->mouseIn, KEY_UP, GLFW_MOUSE_BUTTON_LAST );

		if( this->currentWindow == nullptr )
		{
			this->currentWindow = this;
		}
	}

	Window::~Window()
	{
		glfwDestroyWindow( this->handle );
		glfwTerminate();
	}

	void error_callback( int error, const char* description )
	{
		printf( "GLFW error %d: '%s'\n", error, description );
	}

	void Window::SetTitle( std::string title )
	{
		glfwSetWindowTitle( this->handle, title.c_str() );
	}

	void Window::Close() const
	{
		glfwSetWindowShouldClose( this->handle, GL_TRUE );
	}

	bool Window::IsClosing() const
	{
		return ( glfwWindowShouldClose( this->handle ) ? true : false );
	}

	Vector2 Window::GetSize() const
	{
		int x, y;

		glfwGetWindowSize( this->handle, &x, &y );
		return Vector2( x, y );
	}

	void Window::SwapBuffer() const
	{
		glfwSwapBuffers( this->handle );
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

		glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 2 );
		glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
		glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

		glfwSetErrorCallback( error_callback );
		if( !glfwInit() )
		{
			std::cout << "GLFW could not initialize!\n";
			return false;
		}
		this->handle = glfwCreateWindow( (int) width, (int) height, title.c_str(), nullptr, nullptr );

		int major = glfwGetWindowAttrib( this->handle, GLFW_CONTEXT_VERSION_MAJOR );
		int minor = glfwGetWindowAttrib( this->handle, GLFW_CONTEXT_VERSION_MINOR );
		int revision = glfwGetWindowAttrib( this->handle, GLFW_CONTEXT_REVISION );
		std::cout << "OpenGL Version " << major << "." << minor << "." << revision << std::endl;

		if( !this->handle )
		{
			std::cout << "Failed to create GLFW window!\n";
			glfwTerminate();
			return false;
		}
		glfwMakeContextCurrent( this->handle );
		glfwSwapInterval( 1 );
		this->SetCallbacks();

		/****** END *******/

		/*****/
		/* GLAD Initialization
		/*****/

		if( !gladLoadGLLoader( GLADloadproc( glfwGetProcAddress ) ) )
		{
			std::cout << "Failed to initialize OpenGL context" << std::endl;
			return false;
		}

		/****** END *******/

		glEnable( GL_DEPTH_TEST );

		glViewport( 0, 0, (GLsizei) width, (GLsizei) height );

		//glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
		//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		return true;
	}
}