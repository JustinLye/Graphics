#include<iostream>
#include<mutex>
#if !defined(GLEW_STATIC)
#define GLEW_STATIC
#endif
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#if !defined(__JLG_WINDOW_CONTEXT_HEADER__)
#define __JLG_WINDOW_CONTEXT_HEADER__

namespace jlg {
	enum {
		JLG_ERROR_ID_WINDOW_CONTEXT_UNKNOWN = 0,
		JLG_ERROR_ID_WINDOW_CONTEXT_INIT_GLEW,
		JLG_ERROR_ID_WINDOW_CONTEXT_INIT_GLFW,
		JLG_ERROR_ID_WINDOW_CONTEXT_CREATE,
		JLG_ERROR_ID_WINDOW_CONTEXT_VIEWPORT
	};

	class ContextError {
		const GLchar* _msg;
	public:
		static const GLchar* JLG_ERROR_MSG_WINDOW_CONTEXT_UNKNOWN;
		static const GLchar* JLG_ERROR_MSG_WINDOW_CONTEXT_INIT_GLEW;
		static const GLchar* JLG_ERROR_MSG_WINDOW_CONTEXT_INIT_GLFW;
		static const GLchar* JLG_ERROR_MSG_WINDOW_CONTEXT_CREATE;
		static const GLchar* JLG_ERROR_MSG_WINDOW_CONTEXT_VIEWPORT;
		ContextError();
		ContextError(GLuint error_id);
		ContextError(const GLchar* error_msg);
		inline const GLchar* what() const { return _msg; }
	};

	class WindowContext {
		static std::once_flag _glew_init;
		static std::once_flag _glfw_init;
		static std::once_flag _first_create;
		static void _init_glew();
		static void _init_glfw();
		static void _set_view_port(GLFWwindow* window);
	public:
		static GLFWwindow* CreateWindow(
			const GLuint& w,
			const GLuint& h,
			const GLchar* t);
	protected:
		WindowContext() {}
		WindowContext(const WindowContext&) {}
		WindowContext(WindowContext&&) {}

	};

}

#endif