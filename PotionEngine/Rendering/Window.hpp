#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <string>
#include <iostream>

#include <GL/glew.h>
#include <GLFW\glfw3.h>

#include "..\Math\Vector2.hpp"

namespace Potion
{

	class Window
	{

	public:
		Window();
		~Window();

		bool Create( const std::string& title, unsigned int width, unsigned int height );
		void SetTitle( std::string title );

		void SwapBuffer() const;
		void PollEvents() const;

		void Close() const;
		bool IsClosing() const;

		Vector2 GetSize() const;

		Vector2 GetMousePosition() const;
		void SetMouse( int x, int y );
		void SetMouse( const Vector2& pos );

		void ShouldCaptureMouse( bool capture );

		void SetKeyState( int key, int action );
		void SetMouseState( int key, int action );

		void UpdateKeyHolding();

		/*
		 * Returns true while the user holds down the key identified by name. Think auto fire.
		 *
		 * The list of key identifiers can be found at: http://www.glfw.org/docs/latest/group__keys.html
		 */
		bool GetKey( int key );

		/*
		 * Returns true during the frame the user starts pressing down the key identified by name.
		 *
		 * You should call this function from the Update function, since the state gets reset each frame. It will not return true until the user has released the key and pressed it again.
		 *
		 * The list of key identifiers can be found at: http://www.glfw.org/docs/latest/group__keys.html
		 */
		bool GetKeyDown( int key );

		/*
		 * Returns true during the frame the user releases the key identified by name.
		 *
		 * You should call this function from the Update function, since the state gets reset each frame. It will not return true until the user has pressed the key and released it again.
		 *
		 * The list of key identifiers can be found at: http://www.glfw.org/docs/latest/group__keys.html
		 */
		bool GetKeyUp( int key );

		static Window* m_currentWindow;

	private:
		void SetCallbacks() const;

		static void OnChar( GLFWwindow* window, unsigned int ch );
		static void OnKey( GLFWwindow* window, int key, int scancode, int action, int mods );
		static void OnMouse( GLFWwindow* window, int button, int action, int mods );
		static void OnScroll( GLFWwindow* window, double x, double y );
		static void OnMousePos( GLFWwindow* window, double x, double y );
		static void OnFocus( GLFWwindow* window, int focus );

		GLFWwindow* m_handle;

		unsigned char m_keysIn[ GLFW_KEY_LAST ];
		unsigned char m_mouseIn[ GLFW_MOUSE_BUTTON_LAST ];

	};

}

#endif // _WINDOW_HPP_