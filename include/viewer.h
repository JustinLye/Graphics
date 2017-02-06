
#if !defined(__JLG_VIEWER_HEADER__)
#define __JLG_VIEWER_HEADER__
#include "window.h"
#include "shape_mgr.h"
#include "shading_mgr.h"


namespace jlg {
	class viewer {
	public:
		viewer(
			const GLuint& Width,
			const GLuint& Height,
			const GLchar* Title,
			const GLchar* Vertex_Shader_Path,
			const GLchar* Fragment_Shader_Path);
		jlg::Window window;
		jlg::shape_mgr shapes;
		jlg::basic_shading_mgr shader;
		virtual inline void update() {
			_current_frame = glfwGetTime();
			_delta_time = _current_frame - _last_frame;
			jlg::camera_mgr::do_movement(_delta_time);
			window.Render();
			shader.apply();
			shapes.draw();
			glfwSwapBuffers(window.Handle());
			_last_frame = _current_frame;
		}
	protected:
		jlg::camera _camera;
	private:
		GLfloat _current_frame;
		GLfloat _last_frame;
		GLfloat _delta_time;
	};
};


#endif