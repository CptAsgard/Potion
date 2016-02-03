#include "Window.hpp"

namespace Potion
{

	void Window::OnKey( GLFWwindow* window, int key, int scancode, int action, int mods )
	{

	}

	void Window::OnMouse( GLFWwindow* window, int button, int action, int mods )
	{

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

	void Window::SetCallbacks() const
	{
		glfwSetKeyCallback( this->Handle, this->OnKey );
		glfwSetMouseButtonCallback( this->Handle, this->OnMouse );
		glfwSetScrollCallback( this->Handle, this->OnScroll );
		glfwSetCharCallback( this->Handle, this->OnChar );
		glfwSetCursorPosCallback( this->Handle, this->OnMousePos );
		glfwSetWindowFocusCallback( this->Handle, this->OnFocus );
	}

	Window::Window()
	{
		this->Handle = nullptr;
	}

	Window::~Window()
	{
		glfwDestroyWindow( this->Handle );
		glfwTerminate();
	}

	void error_callback( int error, const char* description )
	{
		printf( "GLFW error %d: '%s'\n", error, description );
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

		this->Handle = glfwCreateWindow( (int) width, (int) height, title.c_str(), nullptr, nullptr );
		if( this->Handle == nullptr ) {
			std::cout << "Failed to create GLFW window!\n";
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent( this->Handle );

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

	void Window::Close() const
	{
		glfwSetWindowShouldClose( this->Handle, GL_TRUE );
	}

	bool Window::IsClosing() const
	{
		return (glfwWindowShouldClose( this->Handle ) ? true : false);
	}

	void Window::SwapBuffer() const
	{
		glfwSwapBuffers( this->Handle );
	}

	void Window::PollEvents() const
	{
		glfwPollEvents();
	}

}