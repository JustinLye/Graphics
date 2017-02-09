#include"jlg/window.h"

jlg::ClearColor::ClearColor() : Red(0.0f), Green(0.0f), Blue(0.0f), Alpha(1.0f) {}
jlg::ClearColor::ClearColor(const GLfloat& c, const GLfloat& a) :
	Red(c), Green(c), Blue(c), Alpha(a) {}
jlg::ClearColor::ClearColor(const GLfloat& r, const GLfloat& g, const GLfloat& b, const GLfloat& a) :
	Red(r), Green(g), Blue(b), Alpha(a) {}
jlg::ClearColor::ClearColor(std::initializer_list<GLfloat> colors) :
	Red(0.0f), Green(0.0f), Blue(0.0f), Alpha(1.0f) {
	auto c = colors.begin();
	switch (colors.size()) {
	case 1:
		Red = Green = Blue = *c;
		break;
	case 2:
		Red = Green = Blue = *c;
		Alpha = *(c+1);
		break;
	case 3:
		Red = *c;
		Green = *(c+1);
		Blue = *(c+2);
		break;
	case 4:
		Red = *c;
		Green = *(c + 1);
		Blue = *(c + 2);
		Alpha = *(c+3);
		break;
	default:
		std::cerr << __FILE__ << '(' << __LINE__ << ") error::ClearColor constructor::Wrong number of arguments passed to constructor" << std::endl;
		throw std::runtime_error("failed to construct ClearColor");
		break;
	};
}


void jlg::WindowContext::_initialize_glfw() {
	
	try {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	} catch (...) {
		std::cerr << __FILE__ << '(' << __LINE__ << ") error::WindowContext _initialize_glfw::Problem with initialization" << std::endl;
	}
	_is_init_glfw = true;
}

void jlg::WindowContext::_initialize_glew() {
	try {
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) {
			throw std::runtime_error("error::WindowContext _initialize_glew()::Problem with GLEW initialization");
		}
		glEnable(GL_DEPTH_TEST);
	} catch (std::runtime_error& re) {
		std::cerr << __FILE__ << '(' << __LINE__ << ')' << re.what() << std::endl;
		throw;
	} catch (...) {
		std::cerr << __FILE__ << '(' << __LINE__ << ')' << "error::WindowContext _initialize_glew()::Problem with GLEW initialization" << std::endl;
		throw;
	}
	_is_init_glew = true;
}

GLFWwindow* jlg::WindowContext::_swap_current() {
	GLFWwindow* current_context = nullptr;
	try {
		std::lock_guard<std::mutex> locker(_mu_context);
		if((current_context = glfwGetCurrentContext()) != _context_handle)
			glfwMakeContextCurrent(_context_handle);
	} catch(...) {
		throw;
	}
	return current_context;
}

void jlg::WindowContext::_make_current(GLFWwindow* _context) {
	try {
		std::lock_guard<std::mutex> locker(_mu_context);
		if (_context != nullptr) {
			glfwMakeContextCurrent(_context);
		}
	} catch (...) {
		throw;
	}
}

void jlg::WindowContext::_create() {
	try {
		_context_handle = glfwCreateWindow(_w, _h, _t, nullptr, nullptr);
		if (!_context_handle)
			throw std::runtime_error("error::WindowContext _create() -> failed to create window.");
		try {
			std::lock_guard<std::mutex> locker(_mu_create);
			GLFWwindow* current_context = _swap_current();
			std::call_once(_flag_firstwin, [&]() { _initialize_glew(); });
			glfwGetFramebufferSize(_context_handle, &_sw, &_sh);
			glViewport(0, 0, _sw, _sh);
			_make_current(current_context);
		} catch (...) {
			throw std::runtime_error("error::WindowContext _create(). Window was created but some other exception was thrown.");
		}
	} catch (...) {
		throw;
	}
}


/* not really sure how I am going to handle modifying OpenGL context safely */
jlg::WindowContext::WindowContext(
	const GLuint& w,
	const GLuint& h,
	const GLchar* t,
	const ClearColor* const c,
	const GLbitfield& buf) :
	_w(w), _h(h), _t(t), _color(c != nullptr ? *c : ClearColor()), _clear_buffer_bit_field(buf) {	
	try {
		std::call_once(_flag_init, [&]() {_initialize_glfw(); });
		try{
		    _create();
		} catch(std::runtime_error& re) {
			std::cerr << __FILE__ << '(' << __LINE__ << ')' << re.what() << std::endl;
			throw;
		} catch (...) {
			throw;
		}
	} catch (...) {
		std::cerr << __FILE__ << '(' << __LINE__ << ')' << "error::WindowContext constructor failed." << std::endl;
		throw;
	}	
}

void jlg::WindowContext::AddClearBufferOption(const GLbitfield& buf) {
	try {
		std::lock_guard<std::mutex> locker(_mu_bufbit);
		_clear_buffer_bit_field = _clear_buffer_bit_field | buf;
	} catch (...) {
		std::cerr << __FILE__ << '(' << __LINE__ << ')' << "error::WindowContext AddClearBufferOption(). Problem occurred modifying buffer bit.";
		throw;
	}
}

void jlg::WindowContext::ResetClearBuffer() {
	try {
		std::lock_guard<std::mutex> locker(_mu_bufbit);
		_clear_buffer_bit_field.ResetBufferBit();
	} catch (...) {
		std::cerr << __FILE__ << '(' << __LINE__ << ')' << "error::WindowContext ResetClearBuffer(). Problem occurred modifying buffer bit.";
	}
}

const GLbitfield& jlg::WindowContext::BufferBitField() {
	try {
		std::lock_guard<std::mutex> locker(_mu_bufbit);
		return _clear_buffer_bit_field();
	} catch (...) {
		std::cerr << __FILE__ << '(' << __LINE__ << ')' << "error::WindowContext BufferBitField(). Problem occurred retriving buffer bit.";
	}
}