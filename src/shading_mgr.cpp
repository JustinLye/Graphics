#include"shading_mgr.h"

jlg::basic_shading_mgr::basic_shading_mgr() :
	texture_shader() {}

jlg::basic_shading_mgr::basic_shading_mgr(const char* vertex_shader_path, const char* fragment_shader_path) :
	texture_shader(vertex_shader_path, fragment_shader_path) {}

void jlg::basic_shading_mgr::apply(
	const char* model_lbl,
	const char* view_lbl,
	const char* proj_lbl) {
	_shader.use_program();
	_texture_mgr.set_uniform();
	glUniformMatrix4fv(
		glGetUniformLocation(_shader.program, model_lbl),
		1,
		GL_FALSE,
		glm::value_ptr(glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -3.0f))));
	glUniformMatrix4fv(
		glGetUniformLocation(_shader.program, view_lbl),
		1,
		GL_FALSE,
		glm::value_ptr(camera_mgr::view_matrix()));
	glUniformMatrix4fv(
		glGetUniformLocation(_shader.program, proj_lbl),
		1,
		GL_FALSE,
		glm::value_ptr(camera_mgr::proj_matrix()));
}