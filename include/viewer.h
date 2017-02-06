
#if !defined(__JLG_VIEWER_HEADER__)
#define __JLG_VIEWER_HEADER__
#include "jlg_window.h"
#include "Shader.h"
#include "shape_mgr.h"

namespace jlg {
	class viewer {
	public:
		viewer(
			const GLuint& Width,
			const GLuint& Height,
			const GLchar* Title,
			const GLchar* Vertex_Shader_Path,
			const GLchar* Fragment_Shader_Path);
		virtual inline void set_window_background_color(
			const GLfloat& Red,
			const GLfloat& Green,
			const GLfloat& Blue,
			const GLfloat& Alpha) {
			_window.SetColor(Red, Green, Blue, Alpha);
		}
		virtual inline void gen_shape(GLuint& shape_id, GLfloat* data, const GLuint& Dimensions, const GLuint& Count) {
			_shape_manager.gen_shape(shape_id, data, Dimensions, Count);
		}
		virtual inline void add_shape_attrib(const GLuint& shape_id, const GLuint& Count) {
			_shape_manager.add_shape_attrib(shape_id, Count);
		}
		virtual inline void buffer() {
			_shape_manager.buffer();
		}
		virtual inline void update() const {
			_window.Render();
			_shader.use_program();
			glBindVertexArray(_vao);
			_shape_manager.draw();
			glBindVertexArray(0);
			glfwSwapBuffers(_window.Handle());
		}
		virtual inline bool should_close() { return glfwWindowShouldClose(_window.Handle()); }
	protected:
		jlg::Window _window;
		jlg::shader _shader;
		jlg::shape_mgr _shape_manager;
	private:
		GLuint _vao;
		GLuint _vbo;
	};
};


#endif