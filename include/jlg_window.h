#include<iostream>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#if !defined(__JLG_WINDOW_HEADER__)
#define __JLG_WINDOW_HEADER__

namespace jlg {

	class Window {
	public:
		Window(const GLuint& Width, const GLuint& Height, const GLchar* Title, bool make_current = true);
		virtual inline GLFWwindow* Handle() const { return this->_window; }
		virtual void SetViewport();
	protected:
		GLFWwindow* _window;
		GLuint _width;
		GLuint _height;
		const GLchar* _title;
		int _screen_width;
		int _screen_height;
		virtual void _create_window(bool make_current);
		virtual void _init() const;
	private:
		static bool _is_initialized;
		static bool _is_first_window;
		bool _is_created;
	};
};


#endif