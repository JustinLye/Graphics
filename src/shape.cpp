#include"../include/shape.h"

#include"../include/shape.h"

jlg::vertex_data::vertex_data(GLfloat* data, const GLuint& Dimensions, const GLuint& Count) :
	_data(nullptr),
	_dims(Dimensions),
	_count(Count) {
	_data = new GLfloat[_dims * _count];
	for(GLuint i = 0; i < (_dims * _count); i++)
		_data[i] = data[i];
}

jlg::vertex_data::~vertex_data() {
	if (_data != nullptr) {
		GLfloat* del_buffer = _data;
		_data = nullptr;
		delete[] del_buffer;
	}
}

jlg::shape::shape(GLfloat* VertexData, const GLuint& Dimensions, const GLuint& VertexCount) :
	vertex_data(VertexData, Dimensions, VertexCount) {}