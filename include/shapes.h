#pragma once
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"SOIL2\SOIL2.h"

namespace jlg {
	class Shape {
	protected:
		//member variables
		GLsizeiptr size;
		GLuint vertexDim; //number of elemnts per vertex
		GLuint vertexCount; //total number of vertices
		GLuint elementCount; //total elements in vertex data array
		GLfloat* vertexData; //vertex data array
		virtual void AllocateVertexData() = 0;

	public:
		Shape(GLuint VertexDim, GLuint VertexCount);
		virtual ~Shape();
		virtual inline const GLvoid* VertexData() { return vertexData; }
		virtual inline GLuint VertexDim() const { return vertexDim; }
		virtual inline GLuint VertexCount() const { return vertexCount; }
		virtual inline GLsizei Stride() const { return (GLfloat)vertexDim * sizeof(GLfloat); }
		virtual inline GLsizeiptr Size() const { return (GLfloat)elementCount * sizeof(GLfloat); }
		virtual inline GLuint ElementCount() const { return elementCount; }
		virtual void Scale(const GLfloat& Multiplier);
	};

	enum CubePoint {
		BOTTOM_BACK_LEFT,
		BOTTOM_FRONT_LEFT,
		BOTTOM_BACK_RIGHT,
		BOTTOM_FRONT_RIGHT,
		TOP_BACK_LEFT,
		TOP_FRONT_LEFT,
		TOP_BACK_RIGHT,
		TOP_FRONT_RIGHT
	};

	class Cube : public Shape {
	protected:
		void AllocateVertexData();
		GLfloat* points;
		GLuint* indices;
		const GLuint* vertexArrayPtr;
	public:
		Cube();
		void BindBuffer(const GLuint& VertexArrayObject, const GLuint& VertexBufferObject, const GLuint& ElementBufferObject);
		void Draw();
	};



};

