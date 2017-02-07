#include"jlg/base/shape_mgr.h"

jlg::shape_mgr::shape_mgr() {}

void jlg::shape_mgr::add_shape(GLuint& shape_id, const GLfloat* data, const GLuint& Dimensions, const GLuint& Count) {
	GLuint vao;
	GLuint vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1,&vbo);
	_vertex_buffer_array_objs.push_back(vao);
	_buffer_objs.push_back(vbo);
	_shapes.push_back(jlg::shape(data, Dimensions, Count));
	shape_id = (GLuint)(_shapes.size() - 1);
}

void jlg::shape_mgr::add_shape(GLuint& shape_id, const shape& copy_shape) {
	GLuint vao;
	GLuint vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	_vertex_buffer_array_objs.push_back(vao);
	_buffer_objs.push_back(vbo);
	_shapes.push_back(jlg::shape(copy_shape));
	shape_id = (GLuint)(_shapes.size() - 1);
}

void jlg::shape_mgr::add_shape_attrib(const GLuint& shape_id, const GLuint& Count) {
	_shapes[shape_id].add_attrib(Count);
}

void jlg::shape_mgr::buffer() {
	for (GLuint i = 0; i < _shapes.size(); i++) {
		_shapes[i].buffer(_vertex_buffer_array_objs[i], _buffer_objs[i]);
	}
}

void jlg::shape_mgr::draw() const {
	for (GLuint i = 0; i < _shapes.size(); i++) {
		glBindVertexArray(_vertex_buffer_array_objs[i]);
		glBindBuffer(GL_ARRAY_BUFFER, _buffer_objs[i]);
		_shapes[i].draw();
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}