#include<iostream>
#if !defined(__JLG_CAMERA_MGR_HEADER__)
#define __JLG_CAMERA_MGR_HEADER__

#include "jlg/base/camera.h"
#include<glm/gtc/type_ptr.hpp>

namespace jlg {
	class camera_mgr {
	public:
		static bool bind_camera(
			jlg::camera* init_camera,
			GLFWwindow* window,
			const GLfloat& width = 800,
			const GLfloat& height = 600,
			const GLfloat& near_clip = 0.1f,
			const GLfloat& far_clip = 1000.0f);
		static void do_movement(GLfloat delta_time);
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);		
		inline static void set_program_id(const GLuint& program_id) { _program_id = program_id; }
		inline static glm::mat4 view_matrix() { return _camera->GetViewMatrix(); }
		inline static glm::mat4 proj_matrix() {
			return glm::perspective(_camera->Zoom, _aspect_ratio, _near_clip, _far_clip);
		}
		inline static GLfloat camera_zoom() { return _camera->Zoom; }
		inline static GLfloat aspect_ratio() { return _aspect_ratio; }
	private:
		static bool _is_set;
		static jlg::camera* _camera;
		static bool _keys[1024];
		static GLfloat _last_x;
		static GLfloat _last_y;
		static GLfloat _aspect_ratio;
		static GLfloat _near_clip;
		static GLfloat _far_clip;
		static bool _first_mouse;
		static GLuint _program_id;
		static void set_callbacks(GLFWwindow* window);
	};
};

#endif