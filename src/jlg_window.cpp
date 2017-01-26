#include"jlg_window.h"

bool jlg::env::_initialized = false;
GLFWwindow* jlg::env::saved_context = NULL;
bool jlg::env::_glew_is_initialized = false;

jlg::env::env() {
	if (!_initialized) {
		this->_initialize_environment();
		_initialized = true;
	}
}

void jlg::env::lock_context(GLFWwindow* WindowContext) {
	GLFWwindow* current_context = glfwGetCurrentContext();
	if (current_context != NULL) {
		if (current_context != WindowContext) {
			saved_context = current_context;
		}
	}
	glfwMakeContextCurrent(WindowContext);
}

void jlg::env::unlock_context(GLFWwindow* WindowContext) {
	GLFWwindow* current_context = glfwGetCurrentContext();
	if (current_context == NULL) {
		std::cerr << "Attempt to unlock context failed. Context is not set." << std::endl;
	} else if (current_context != WindowContext) {
		std::cerr << "Attempt to unlock context failed. Context can only be unlock by passing handle to current context." << std::endl;
	} else if (current_context == WindowContext) {
		glfwMakeContextCurrent(saved_context);
	}
}

GLFWwindow* jlg::env::create_window(const GLuint& Width, const GLuint& Height, const GLchar* Title) {
	GLFWwindow* window = glfwCreateWindow(
		Width,
		Height,
		Title,
		nullptr,
		nullptr);
	lock_context(window);
	if (!_glew_is_initialized) {
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) {
			std::cerr << "ERROR::INITILIZATION::EXTENSION WRANGLER::FAILED TO INITIALIZE" << std::endl;
			glfwTerminate();
			return nullptr;
		}
		_glew_is_initialized = true;
	}
	glEnable(GL_DEPTH_TEST);
	unlock_context(window);
	return window;
}

void jlg::env::_initialize_environment() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}


jlg::Window::Window(const GLuint& Width, const GLuint& Height, const GLchar* Title) :
	env(),
	_window(nullptr),
	_width(Width),
	_height(Height),
	_title(Title),
	_screen_width(0),
	_screen_height(0) {
	this->_create_window();
}

void jlg::Window::_create_window() {
	this->_window = create_window(
		this->_width,
		this->_height,
		this->_title);
	glfwGetFramebufferSize(this->_window, &this->_screen_width, &this->_screen_height);
	glViewport(this->_width, this->_height, this->_screen_width, this->_screen_height);
}

void jlg::Window::_clear_color_buffer() const {
	GLfloat currentFrame = glfwGetTime();
	GLfloat greenValue = (sin(currentFrame) / 2) + 0.5;
	glClearColor(0.5f, greenValue, 0.20f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void jlg::AppWindow::ClearColorBuffer() const {
	if (IsCurrent(this->_window)) {
		_clear_color_buffer();
	} else {
		lock_context(this->_window);
		_clear_color_buffer();
		unlock_context(this->_window);
	}
}