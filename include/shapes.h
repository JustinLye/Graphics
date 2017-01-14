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
		~Shape();
		inline const GLvoid* VertexData() { return vertexData; }
		inline GLuint VertexDim() const { return vertexDim; }
		inline GLuint VertexCount() const { return vertexCount; }
		inline GLsizei Stride() const { return (GLfloat)vertexDim * sizeof(GLfloat); }
		inline GLsizeiptr Size() const { return (GLfloat)elementCount * sizeof(GLfloat); }
		inline GLuint ElementCount() const { return elementCount; }
		void Scale(const GLfloat& Multiplier);
	};

	class Cube : public Shape {
	protected:
		void AllocateVertexData();
	public:
		Cube();


	};

};

