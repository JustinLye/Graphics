#include"model_mgr.h"

jlg::model_mgr::model_mgr() {}

void jlg::model_mgr::add_model(
	GLuint& model_id,
	GLfloat* data,
	const GLuint& dimensions,
	const GLuint& vertex_count,
	const glm::vec3& init_position,
	const GLfloat& init_angle,
	const glm::vec3& init_rotation_axis) {
	GLuint vao;
	GLuint vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	_vertex_buffer_array_objs.push_back(vao);
	_buffer_objs.push_back(vbo);
	_models.push_back(jlg::model(data, dimensions, vertex_count, init_position, init_angle, init_rotation_axis));
	model_id = (GLuint)(_models.size() - 1);
}

void jlg::model_mgr::add_attrib(const GLuint& model_id, const GLuint& Count) {
	_models[model_id].add_attrib(Count);
}

void jlg::model_mgr::buffer() {
	for (GLuint i = 0; i < _models.size(); i++)
		_models[i].buffer(_vertex_buffer_array_objs[i], _buffer_objs[i]);
}

void jlg::model_mgr::draw() const {
	for (GLuint i = 0; i < _models.size(); i++) {
		glBindVertexArray(_vertex_buffer_array_objs[i]);
		glBindBuffer(GL_ARRAY_BUFFER, _buffer_objs[i]);
		_models[i].draw();
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}