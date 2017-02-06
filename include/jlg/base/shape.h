
#include<vector>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#if !defined(__JLG_SHAPE_HEADER__)
#define __JLG_SHAPE_HEADER__

namespace jlg {

	class vertex_data {
	public:
		vertex_data(GLfloat* data, const GLuint& Dimensions, const GLuint& Count);
		vertex_data(const vertex_data& other);
		~vertex_data();
		inline GLsizeiptr vertex_size() const { return (_dims * _count) * sizeof(GLfloat); }
		inline GLfloat* vertices() { return _data; }
		inline GLuint vertex_count() const { return _count; }
		inline GLuint vertex_dims() const { return _dims; }
	private:
		GLfloat* _data;
		GLuint _dims;
		GLuint _count;
	};

	struct attribute {
		GLuint index;
		GLuint count;
		GLuint stride;
		GLuint offset;
		attribute() :
			index(0),
			count(0),
			stride(0),
			offset(0) {}
		attribute(
			const GLuint& Index,
			const GLuint& Count,
			const GLuint& Stride,
			const GLuint& Offset) :
			index(Index),
			count(Count),
			stride(Stride),
			offset(Offset) {}
	};

	class shape : public vertex_data {
	public:
		shape(GLfloat* VertexData, const GLuint& Dimensions, const GLuint& VertexCount);
		shape(const vertex_data& copy_data);
		virtual void add_attrib(const GLuint& Count);
		virtual void buffer(const GLuint& generated_vao, const GLuint& generated_vbo);
		virtual void draw() const;
	protected:
		std::vector<attribute> attribs;
	private:
		GLuint _next_index;
		GLuint _total_count;
	};
};
#endif