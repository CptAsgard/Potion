#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <string>
#include <iostream>

#include <GL/glew.h>
#include <GLFW\glfw3.h>

namespace Potion
{

	class Window
	{

	public:
		Window();
		~Window();

		bool Create( const std::string& title, unsigned int width, unsigned int height );

		void SwapBuffer() const;

		void PollEvents() const;

		void Close() const;
		bool IsClosing() const;

	private:
		void SetCallbacks() const;

		static void OnChar( GLFWwindow* window, unsigned int ch );
		static void OnKey( GLFWwindow* window, int key, int scancode, int action, int mods );
		static void OnMouse( GLFWwindow* window, int button, int action, int mods );
		static void OnScroll( GLFWwindow* window, double x, double y );
		static void OnMousePos( GLFWwindow* window, double x, double y );
		static void OnFocus( GLFWwindow* window, int focus );

		GLFWwindow* Handle;

	};

}

#endif // _WINDOW_HPP_