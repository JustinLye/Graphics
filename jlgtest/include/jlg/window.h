#include<thread>
#include<mutex>
#include<initializer_list>
#if !defined(__JLG_WINDOW_HEADER_TEST__)
#define __JLG_WINDOW_HEADER_TEST__
#if !defined(GLEW_STATIC)
#include<iostream>
#define GLEW_STATIC
#endif
#include<GL/glew.h>
#include<GLFW/glfw3.h>

namespace jlg {
	
	class ClearColor {
		inline void output(std::ostream& s) const {
			s << '(' << Red << ',' << Green << ',' << Blue << ',' << Alpha << ')';
		}
	public:
		GLfloat Red;
		GLfloat Green;
		GLfloat Blue;
		GLfloat Alpha;
		ClearColor();
		ClearColor(const GLfloat& c, const GLfloat& a = 1.0f);
		ClearColor(const GLfloat& r, const GLfloat& g, const GLfloat& b, const GLfloat& a = 1.0f);
		ClearColor(std::initializer_list<GLfloat> colors);
		inline friend std::ostream& operator<<(std::ostream& s, const ClearColor& c) {
		    c.output(s);
			return s;
		}
	};

	class ClearBufferBit {
		GLbitfield _buffer_bit;
	public:
		ClearBufferBit() : _buffer_bit(0) {}
		ClearBufferBit(const GLbitfield& init_buff) : _buffer_bit(init_buff) {}
		inline void ResetBufferBit() { _buffer_bit = 0; }
		inline const GLbitfield& operator()() const { return _buffer_bit; }
		inline ClearBufferBit& operator|(const GLbitfield& buf) {
			_buffer_bit = _buffer_bit | buf;
			return *this;
		}
	};

	class WindowContext {
		std::mutex _mu_render;
		std::mutex _mu_context;
		std::mutex _mu_create;
		std::mutex _mu_bufbit;
		std::mutex _mu_color;
		std::once_flag _flag_init;
		std::once_flag _flag_firstwin;
		std::once_flag _flag_context_locker;
		bool _is_init_glfw;
		bool _is_init_glew;
		bool _is_created;
		ClearBufferBit _clear_buffer_bit_field;
		ClearColor _color;
		GLFWwindow* _context_handle;
		GLuint _w;
		GLuint _h;
		const GLchar* _t;
		int _sw;
		int _sh;
		void _initialize_glfw();
		void _initialize_glew();
		void _create();
		GLFWwindow* _swap_current();
		void _make_current(GLFWwindow* _context);
	public:
		inline GLFWwindow* const ContextHandle() const { return _context_handle; }
		inline const GLuint& Width() const { return _w; }
		inline const GLuint& Height() const { return _h; }
		inline const int& ScreenWidth() const { return _sw; }
		inline const int& SrceenHeight() const { return _sh; }
		void AddClearBufferOption(const GLbitfield& buf);
		void ResetClearBuffer();
		const GLbitfield& BufferBitField();
		inline void Color(const GLfloat& c, const GLfloat& a = 1.0f) {
			try {
				std::lock_guard<std::mutex> locker(_mu_color);
				_color = { c, c, c };
			} catch (...) { throw; }
		}
		inline void Color(const GLfloat& r, const GLfloat& g, const GLfloat& b, const GLfloat& a = 1.0f) {
			try {
				std::lock_guard<std::mutex> locker(_mu_color);
				_color = { r, g, b, a };
			} catch (...) { throw; }
		}
		inline void Color(const ClearColor& c) {
			try {
				std::lock_guard<std::mutex> locker(_mu_color);
				_color = c;
			} catch (...) { throw; }
		}
		inline bool IsInitialized() const { return _is_init_glew && _is_init_glfw; }
		inline bool IsCreated() const { return _is_created; }
		inline bool ClearBuffer() {
			try {
				std::lock_guard<std::mutex> locker(_mu_render);
				try {
					GLFWwindow* current_context = _swap_current();
					try {
						std::lock_guard<std::mutex> locker1(_mu_color);
						glClearColor(_color.Red, _color.Green, _color.Blue, _color.Alpha);
					} catch (...) {
						_make_current(current_context);
						throw;
					}
					try {
						std::lock_guard<std::mutex> locker1(_mu_bufbit);
						glClear(_clear_buffer_bit_field());
					} catch (...) {
						_make_current(current_context);
						throw;
					}
				} catch (...) {
					throw;
				}
			} catch (...) {
				throw;
			}
		}
		WindowContext(const GLuint& w, const GLuint& h, const GLchar* t, const ClearColor* const c = nullptr, const GLbitfield & buf = 0);


	protected:
		WindowContext(const WindowContext&) {}
		WindowContext(WindowContext&&) {}

	};
}

#endif
