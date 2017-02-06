#include"../include/shape.h"


jlg::vertex_data::vertex_data(GLfloat* data, const GLuint& Dimensions, const GLuint& Count) :
	_data(nullptr),
	_dims(Dimensions),
	_count(Count) {
	_data = new GLfloat[_dims * _count];
	for(GLuint i = 0; i < (_dims * _count); i++)
		_data[i] = data[i];
}

jlg::vertex_data::vertex_data(const vertex_data& other) :
	_data(nullptr),
	_dims(other._dims),
	_count(other._count) {
	_data = new GLfloat[_dims * _count];
	for(GLuint i = 0; i < (_dims * _count); i++)
		_data[i] = other._data[i];
}

jlg::vertex_data::~vertex_data() {
	if (_data != nullptr) {
		GLfloat* del_buffer = _data;
		_data = nullptr;
		delete[] del_buffer;
	}
}

jlg::shape::shape(GLfloat* VertexData, const GLuint& Dimensions, const GLuint& VertexCount) :
	vertex_data(VertexData, Dimensions, VertexCount),
	_next_index(0),
	_total_count(0) {}

jlg::shape::shape(const vertex_data& copy_data) :
	vertex_data(copy_data),
	_next_index(0),
	_total_count(0) {}

void jlg::shape::add_attrib(const GLuint& Count) {
	attribs.push_back(attribute(_next_index, Count, vertex_dims(), _total_count));
	_next_index++;
	_total_count += Count;
}

void jlg::shape::buffer(const GLuint& generated_vao, const GLuint& generated_vbo) {
	glBindVertexArray(generated_vao);
	glBindBuffer(GL_ARRAY_BUFFER, generated_vbo);
	glBufferData(GL_ARRAY_BUFFER, this->vertex_size(), this->vertices(), GL_STATIC_DRAW);
	for (GLuint i = 0; i < attribs.size(); i++) {
		glVertexAttribPointer(
			attribs[i].index,
			attribs[i].count,
			GL_FLOAT,
			GL_FALSE,
			this->vertex_dims() * sizeof(GLfloat),
			(GLvoid*)(attribs[i].offset * sizeof(GLfloat)));
		glEnableVertexAttribArray(attribs[i].index);
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
}

void jlg::shape::draw() const {
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)this->vertex_count());
}