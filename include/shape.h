
#include<vector>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#if !defined(__JL_SHAPE_HEADER__)
#define __JL_SHAPE_HEADER__

namespace jlg {

	class vertex_data {
	public:
		vertex_data(GLfloat* data, const GLuint& Dimensions, const GLuint& Count);
		~vertex_data();
		inline GLsizeiptr vertex_size() const { return (_dims * _count) * sizeof(GLfloat); }
		inline GLfloat* vertices() { return _data; }
		inline GLuint vertex_count() const { return _count; }
	private:
		GLfloat* _data;
		GLuint _dims;
		GLuint _count;
	};

	class shape : public vertex_data {
	public:
		shape(GLfloat* VertexData, const GLuint& Dimensions, const GLuint& VertexCount);
	};
};
#endif