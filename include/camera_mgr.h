#if !defined(__JLG_CAMERA_MGR_HEADER__)
#define __JLG_CAMERA_MGR_HEADER__

#include "camera.h"

namespace jlg {
	class camera_mgr {
	public:
		camera_mgr(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f));
		void do_movement(GLfloat delta_time);
		inline void set_program_id(const GLuint& program_id) { _program_id = program_id; }
		void update_mvp();
		inline glm::mat4 get_view_matrix() { return _camera.GetViewMatrix(); }
		inline void process_keyboard(Camera_Movement direction, GLfloat delta_time) {
			_camera.ProcessKeyboard(direction, delta_time);
		}
		inline void process_mouse_movement(GLfloat x_offset, GLfloat y_offset, GLboolean constrain_pitch = true) {
			_camera.ProcessMouseMovement(x_offset, y_offset, constrain_pitch);
		}
		inline void process_scroll(GLfloat y_offset) {
			_camera.ProcessMouseScroll(y_offset);
		}
		bool keys[1024];
		bool first_mouse;
		GLfloat last_x;
		GLfloat last_y;
	protected:
		jlg::camera _camera;
	private:
		GLuint _program_id;
		
	};
};

#endif