#include"camera_mgr.h"


bool jlg::camera_mgr::_is_set = false;
jlg::camera* jlg::camera_mgr::_camera = nullptr;
GLfloat jlg::camera_mgr::_last_x = 0.0f;
GLfloat jlg::camera_mgr::_last_y = 0.0f;
bool jlg::camera_mgr::_first_mouse = true;
GLuint jlg::camera_mgr::_program_id = 0;
GLfloat jlg::camera_mgr::_aspect_ratio = 0.0f;
GLfloat jlg::camera_mgr::_near_clip = 0.1f;
GLfloat jlg::camera_mgr::_far_clip = 1000.0f;
bool jlg::camera_mgr::_keys[1024];
bool jlg::camera_mgr::bind_camera(
	jlg::camera* init_camera,
	GLFWwindow* window,
	const GLfloat& width,
	const GLfloat& height,
	const GLfloat& near_clip,
	const GLfloat& far_clip) {
	bool result = true;
	_is_set ? result = false : _is_set = true;
	if (!result) {
		return result;
	}
	_camera = init_camera;
	_last_x = width / 2.0f;
	_last_y = height / 2.0f;
	_aspect_ratio = width / height;
	_near_clip = near_clip;
	_far_clip = far_clip;
	_first_mouse = true;
	for(int i = 0; i < 1024; i++)
		_keys[i] = false;
	set_callbacks(window);
	return result;
}

void jlg::camera_mgr::do_movement(GLfloat delta_time) {
		if (_keys[GLFW_KEY_W])
			_camera->ProcessKeyboard(jlg::FORWARD, delta_time);
		if (_keys[GLFW_KEY_S])
			_camera->ProcessKeyboard(jlg::BACKWARD, delta_time);
		if (_keys[GLFW_KEY_A])
			_camera->ProcessKeyboard(jlg::LEFT, delta_time);
		if (_keys[GLFW_KEY_D])
			_camera->ProcessKeyboard(jlg::RIGHT, delta_time);
}

void jlg::camera_mgr::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS)
			_keys[key] = true;
		else if (action == GLFW_RELEASE)
			_keys[key] = false;
	}
}

void jlg::camera_mgr::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (_first_mouse) {
		_last_x = xpos;
		_last_y = ypos;
		_first_mouse = false;
	}

	GLfloat xoffset = xpos - _last_x;
	GLfloat yoffset = _last_y - ypos;
	_last_x = xpos;
	_last_y = ypos;
	_camera->ProcessMouseMovement(xoffset, yoffset);
}

void jlg::camera_mgr::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	_camera->ProcessMouseScroll(yoffset);
}
void jlg::camera_mgr::set_callbacks(GLFWwindow* window) {
	glfwSetKeyCallback(window, jlg::camera_mgr::key_callback);
	glfwSetCursorPosCallback(window, jlg::camera_mgr::mouse_callback);
	glfwSetScrollCallback(window, jlg::camera_mgr::scroll_callback);
}