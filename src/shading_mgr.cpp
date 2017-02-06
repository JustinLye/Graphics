#include"shading_mgr.h"

jlg::basic_shading_mgr::basic_shading_mgr() :
	texture_shader() {}

jlg::basic_shading_mgr::basic_shading_mgr(const char* vertex_shader_path, const char* fragment_shader_path) :
	texture_shader(vertex_shader_path, fragment_shader_path) {}

void jlg::basic_shading_mgr::apply(
	const char* view_lbl,
	const char* proj_lbl,
	const char* model_lbl) {
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

void jlg::basic_shading_mgr::apply(glm::mat4& transform) {
	_shader.use_program();
	_texture_mgr.set_uniform();
	glUniformMatrix4fv(
		glGetUniformLocation(_shader.program, "model"),
		1,
		GL_FALSE,
		glm::value_ptr(transform));
	glUniformMatrix4fv(
		glGetUniformLocation(_shader.program, "view"),
		1,
		GL_FALSE,
		glm::value_ptr(camera_mgr::view_matrix()));
	glUniformMatrix4fv(
		glGetUniformLocation(_shader.program, "projection"),
		1,
		GL_FALSE,
		glm::value_ptr(camera_mgr::proj_matrix()));
}

jlg::model_shading_mgr::model_shading_mgr() :
	texture_shader(),
	_model_mgr(nullptr) {}

jlg::model_shading_mgr::model_shading_mgr(
	const char* vertex_shader_path,
	const char* fragment_shader_path) :
	texture_shader(vertex_shader_path, fragment_shader_path),
	_model_mgr(nullptr) {}
jlg::model_shading_mgr::model_shading_mgr(
	const char* vertex_shader_path,
	const char* fragment_shader_path,
	model_mgr* model_manager) :
	texture_shader(vertex_shader_path, fragment_shader_path),
	_model_mgr(model_manager) {}

void jlg::model_shading_mgr::apply() try {
	_shader.use_program();
	_texture_mgr.set_uniform();
	glUniformMatrix4fv(
		glGetUniformLocation(_shader.program, "view"),
		1,
		GL_FALSE,
		glm::value_ptr(jlg::camera_mgr::view_matrix()));
	glUniformMatrix4fv(
		glGetUniformLocation(_shader.program, "projection"),
		1,
		GL_FALSE,
		glm::value_ptr(jlg::camera_mgr::proj_matrix()));
	GLuint model_loc = glGetUniformLocation(_shader.program, "model");
	for (GLuint i = 0; i < _model_mgr->count(); i++) {
		glUniformMatrix4fv(
			model_loc,
			1,
			GL_FALSE,
			glm::value_ptr(_model_mgr->operator[](i).transform()));
		_model_mgr->operator[](i).draw();
	}
} catch (std::exception& e) {
	std::cerr << e.what() << std::endl;
	throw std::exception("ERROR::MODEL SHADING MGR::apply()::method failure");
} catch (...) {
	std::cerr << "Unknow exception occurred" << std::endl;
	throw std::exception("ERROR::MODEL SHADING MGR::apply()::method failure");
}