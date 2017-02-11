
#include<vector>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#if !defined(__JLG_SHAPE_HEADER__)
#define __JLG_SHAPE_HEADER__

namespace jlg {
	/* vertex_data class
	   The primary function of the vertex data class is to be a container for vertices.
	   The structure is an array of floats.
	*/
	class vertex_data {
	public:
		/* GLfloat array data is copied to newly allocated GLfloat array vertex_data::_data.
		   The allocated memory is released when vertex_data is destructed.
		*/
		vertex_data(const GLfloat* data, const GLuint& Dimensions, const GLuint& Count);
		vertex_data(const vertex_data& other);
		~vertex_data();
		inline GLsizeiptr vertex_size() const { return (_dims * _count) * sizeof(GLfloat); }
		inline GLfloat* vertices() const { return _data; }
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
		attribute(const attribute& copy_attrib) :
			index(copy_attrib.index),
			count(copy_attrib.count),
			stride(copy_attrib.stride),
			offset(copy_attrib.offset) {}
	};

	class shape : public vertex_data {
	public:
		shape(const GLfloat* VertexData, const GLuint& Dimensions, const GLuint& VertexCount);
		shape(const vertex_data& copy_data);
		shape(const shape& copy_shape);
		virtual void add_attrib(const GLuint& Count);
		virtual void buffer(const GLuint& generated_vao, const GLuint& generated_vbo) const;
		virtual void draw() const;
	protected:
		std::vector<attribute> attribs;
	private:
		GLuint _next_index;
		GLuint _total_count;
	};
};
#endif