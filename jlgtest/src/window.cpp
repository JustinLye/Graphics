#include"jlg/window.h"

const GLchar* jlg::ContextError::JLG_ERROR_MSG_WINDOW_CONTEXT_UNKNOWN = "error::ContextError::Unknown error occurred.";
const GLchar* jlg::ContextError::JLG_ERROR_MSG_WINDOW_CONTEXT_INIT_GLEW = "error::ContextError::GLEW failed to be initialized.";
const GLchar* jlg::ContextError::JLG_ERROR_MSG_WINDOW_CONTEXT_INIT_GLFW = "error::ContextError::GLFW failed to be initialized.";
const GLchar* jlg::ContextError::JLG_ERROR_MSG_WINDOW_CONTEXT_CREATE = "error::ContextError::Window failed to be created.";
const GLchar* jlg::ContextError::JLG_ERROR_MSG_WINDOW_CONTEXT_VIEWPORT = "error::ContextError::Failed to set viewport.";

jlg::ContextError::ContextError(GLuint error_id) :
	_msg(nullptr) {
	switch (error_id) {
	case JLG_ERROR_ID_WINDOW_CONTEXT_UNKNOWN:
		_msg = JLG_ERROR_MSG_WINDOW_CONTEXT_UNKNOWN;
		break;
	case JLG_ERROR_ID_WINDOW_CONTEXT_INIT_GLEW:
		_msg = JLG_ERROR_MSG_WINDOW_CONTEXT_INIT_GLEW;
		break;
	case JLG_ERROR_ID_WINDOW_CONTEXT_INIT_GLFW:
		_msg = JLG_ERROR_MSG_WINDOW_CONTEXT_INIT_GLFW;
		break;
	case JLG_ERROR_ID_WINDOW_CONTEXT_CREATE:
		_msg = JLG_ERROR_MSG_WINDOW_CONTEXT_CREATE;
		break;
	case JLG_ERROR_ID_WINDOW_CONTEXT_VIEWPORT:
		_msg = JLG_ERROR_MSG_WINDOW_CONTEXT_VIEWPORT;
		break;
	default:
		_msg = JLG_ERROR_MSG_WINDOW_CONTEXT_UNKNOWN;
		break;
	};
}
jlg::ContextError::ContextError(const GLchar* error_msg) : _msg(error_msg) {}
jlg::ContextError::ContextError() : _msg(JLG_ERROR_MSG_WINDOW_CONTEXT_UNKNOWN) {}


std::once_flag jlg::WindowContext::_glew_init;
std::once_flag jlg::WindowContext::_glfw_init;
std::once_flag jlg::WindowContext::_first_create;

void jlg::WindowContext::_init_glew() {
	try {
		if(glewInit() != GLEW_OK)
			throw;
		glewExperimental = GL_TRUE;
		glEnable(GL_DEPTH_TEST);
	} catch (...) {
		throw jlg::ContextError(JLG_ERROR_ID_WINDOW_CONTEXT_INIT_GLFW);
	}
}

void jlg::WindowContext::_init_glfw() {
	try {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	} catch (...) {
		throw jlg::ContextError(JLG_ERROR_ID_WINDOW_CONTEXT_INIT_GLFW);
	}
}

void jlg::WindowContext::_set_view_port(GLFWwindow* window) {
	try {
		int sw, sh;
		glfwGetFramebufferSize(window, &sw, &sh);
		glViewport(0,0, sw, sh);
	} catch (...) {
		throw jlg::ContextError(JLG_ERROR_ID_WINDOW_CONTEXT_VIEWPORT);
	}
}

GLFWwindow* jlg::WindowContext::CreateWindow(
	const GLuint& w,
	const GLuint& h,
	const GLchar* t) {
	GLFWwindow* window = nullptr;
	try {
		std::call_once(_glfw_init, [&]() { _init_glfw(); });
		GLFWwindow* current_context = glfwGetCurrentContext();
		try {
			window = glfwCreateWindow(w, h, t, nullptr, nullptr);
			if (!window)
				throw;
			GLFWwindow* current_context = glfwGetCurrentContext();
			glfwMakeContextCurrent(window);
			std::call_once(_glew_init, [&]() { _init_glew(); });
			_set_view_port(window);
			if(current_context)
				glfwMakeContextCurrent(current_context);
		} catch (...) {
			throw jlg::ContextError(JLG_ERROR_ID_WINDOW_CONTEXT_CREATE);
		}
	} catch (jlg::ContextError& e) {
		std::cerr << e.what() << std::endl;
		throw;
	} catch (...) {
		throw;
	}
	return window;
}