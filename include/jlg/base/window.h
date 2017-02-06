#include<iostream>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#if !defined(__JLG_WINDOW_HEADER__)
#define __JLG_WINDOW_HEADER__

namespace jlg {
	struct clear_color {
		GLfloat r;
		GLfloat g;
		GLfloat b;
		GLfloat a;
		clear_color() :
			r(0.0f),
			g(0.0f),
			b(0.0f),
			a(1.0f) {}
		clear_color(
			const GLfloat& Red,
			const GLfloat& Green,
			const GLfloat& Blue,
			const GLfloat& Alpha) :
			r(Red),
			g(Green),
			b(Blue),
			a(Alpha) {}
	};
	class Window {
	public:
		Window(const GLuint& Width, const GLuint& Height, const GLchar* Title, bool make_current = true);
		virtual inline GLFWwindow* Handle() const { return this->_window; }
		virtual void SetViewport();
		virtual void SetColor(const GLfloat& Red, const GLfloat& Green, const GLfloat& Blue, const GLfloat& Alpha);
		virtual void Render() const;
		inline virtual void hide_cursor(const GLboolean& hide = true) {
			if (hide) {
				glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			} else {
				glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
		}
		inline virtual void lock_cursor(const GLboolean& lock = true) {
			if (lock) {
				glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			} else {
				glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
		}
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
		clear_color _color;
	};
};


#endif