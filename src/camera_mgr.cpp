#include"camera_mgr.h"
#include<glm/gtc/type_ptr.hpp>
jlg::camera_mgr::camera_mgr(glm::vec3 pos) :
	first_mouse(true),
	last_x(400),
	last_y(300),
	_camera(pos) {
	for(int i = 0; i < 1024; i++)
		keys[i] = false;
}

void jlg::camera_mgr::do_movement(GLfloat delta_time) {
	if(keys[GLFW_KEY_W])
		_camera.ProcessKeyboard(jlg::FORWARD, delta_time);
	if(keys[GLFW_KEY_S])
		_camera.ProcessKeyboard(jlg::BACKWARD, delta_time);
	if(keys[GLFW_KEY_A])
		_camera.ProcessKeyboard(jlg::LEFT, delta_time);
	if(keys[GLFW_KEY_D])
		_camera.ProcessKeyboard(jlg::RIGHT, delta_time);
}

void jlg::camera_mgr::update_mvp() {
	GLuint model_loc = glGetUniformLocation(_program_id, "model");
	GLuint view_loc = glGetUniformLocation(_program_id, "view");
	GLuint proj_loc = glGetUniformLocation(_program_id, "projection");
	glm::mat4 view = get_view_matrix();
	glm::mat4 projection = glm::perspective(
		_camera.Zoom,
		800.0f/600.0f,
		0.1f,
		1000.0f);
	glm::mat4 model = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, 20.0f, glm::vec3(1.0f, 0.0f, 0.5f));
	glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
}