#include"jlg_window.h"

bool jlg::Window::_is_initialized = false;
bool jlg::Window::_is_first_window = true;
jlg::Window::Window(const GLuint& Width, const GLuint& Height, const GLchar* Title, bool make_current) :
	_window(nullptr),
	_width(Width),
	_height(Height),
	_title(Title),
	_screen_width(0),
	_screen_height(0),
	_is_created(false) {
	this->_create_window(make_current);
}

void jlg::Window::SetViewport() {
	bool pre_reqs = true;
	if (!_is_initialized) {
		std::cerr << "system must be initialized" << std::endl;
		pre_reqs = false;
	}
	if (!_is_created) {
		std::cerr << "window must be created" << std::endl;
		pre_reqs = false;
	}
	if(!pre_reqs)
		return;
	glfwGetFramebufferSize(_window, &_screen_width, &_screen_height);
	glViewport(0,0, _screen_width, _screen_height);
}

void jlg::Window::SetColor(const GLfloat& Red, const GLfloat& Green, const GLfloat& Blue, const GLfloat& Alpha) {
	_color.r = Red;
	_color.g = Green;
	_color.b = Blue;
	_color.a = Alpha;
}

void jlg::Window::Render() const {
	glClearColor(_color.r, _color.g, _color.b, _color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void jlg::Window::_create_window(bool make_current) {
	if (!_is_initialized) {
		_init();
		_is_initialized = true;
	}
	_window = glfwCreateWindow(
		this->_width,
		this->_height,
		this->_title,
		nullptr,
		nullptr);
	if (make_current) {
		glfwMakeContextCurrent(_window);
	}
	if (_is_first_window) {
		GLFWwindow* curr_win = NULL;
		if (!make_current) {
			curr_win = glfwGetCurrentContext();
			glfwMakeContextCurrent(_window);
		}
		glewExperimental = GL_TRUE;
		glewInit();
		_is_first_window = false;
		if (!make_current) {
			glfwMakeContextCurrent(curr_win);
		}
	}
	_is_created = _window != nullptr;
}

void jlg::Window::_init() const {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glEnable(GL_DEPTH_TEST);
}




