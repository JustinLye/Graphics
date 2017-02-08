#include"jlg/base/shape.h"

/* GLfloat array data is copied to newly allocated GLfloat array vertex_data::_data.
The allocated memory is released when vertex_data is destructed.
*/
jlg::vertex_data::vertex_data(const GLfloat* data, const GLuint& Dimensions, const GLuint& Count) :
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

jlg::shape::shape(const GLfloat* VertexData, const GLuint& Dimensions, const GLuint& VertexCount) :
	vertex_data(VertexData, Dimensions, VertexCount),
	_next_index(0),
	_total_count(0) {}

jlg::shape::shape(const vertex_data& copy_data) :
	vertex_data(copy_data),
	_next_index(0),
	_total_count(0) {}

jlg::shape::shape(const shape& copy_shape) :
	vertex_data(copy_shape.vertices(), copy_shape.vertex_dims(), copy_shape.vertex_count()),
	_next_index(0),
	_total_count(0) {
	for (GLuint i = 0; i < copy_shape.attribs.size(); i++) {
		attribs.push_back(copy_shape.attribs[i]);
		if(_next_index < copy_shape.attribs[i].index)
			_next_index = copy_shape.attribs[i].index;
		_total_count += attribs[i].count;
	}
	_next_index++;
}

void jlg::shape::add_attrib(const GLuint& Count) {
	attribs.push_back(attribute(_next_index, Count, vertex_dims(), _total_count));
	_next_index++;
	_total_count += Count;
}

void jlg::shape::buffer(const GLuint& generated_vao, const GLuint& generated_vbo) const {
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