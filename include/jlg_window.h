#include<iostream>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#if !defined(__JLG_WINDOW_HEADER__)
#define __JLG_WINDOW_HEADER__

namespace jlg {
	class env {
	protected:
		env();
		static void lock_context(GLFWwindow* WindowContext);
		static void unlock_context(GLFWwindow* WindowContext);
		static GLFWwindow* create_window(const GLuint& Width, const GLuint& Height, const GLchar* Title);
		static inline bool IsCurrent(GLFWwindow* WindowContext) { return WindowContext != NULL && WindowContext == saved_context; }
	private:
		static bool _initialized;
		static bool _glew_is_initialized;
		virtual void _initialize_environment();
		static GLFWwindow* saved_context;
	};

	class Window : protected env {
	public:
		Window(const GLuint& Width, const GLuint& Height, const GLchar* Title);
		virtual inline GLFWwindow* Handle() const { return this->_window; }
		virtual void ClearColorBuffer() const = 0;
	protected:
		GLFWwindow* _window;
		GLuint _width;
		GLuint _height;
		const GLchar* _title;
		int _screen_width;
		int _screen_height;
		virtual void _create_window();
		virtual void _clear_color_buffer() const;
	};

	class AppWindow : public Window {
	public:
		AppWindow() : Window(800, 600, "AppWindow"), deltaTime(0.0f), lastFrame(0.0f) {}
		virtual void ClearColorBuffer() const;
	private:
		GLfloat deltaTime;
		GLfloat lastFrame;
	};

};


#endif