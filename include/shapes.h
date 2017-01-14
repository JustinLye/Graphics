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
		GLfloat vertexDim; //number of elemnts per vertex
		GLfloat vertexCount; //total number of vertices
		GLfloat elementCount; //total elements in vertex data array
		GLfloat* vertexData; //vertex data array
		virtual void AllocateVertexData() = 0;

	public:
		Shape(GLfloat VertexDim, GLfloat VertexCount);
		~Shape();
		inline const GLvoid* VertexData() { return vertexData; }
		inline GLfloat VertexDim() const { return vertexDim; }
		inline GLfloat VertexCount() const { return vertexCount; }
		inline GLsizei Stride() const { return vertexDim * sizeof(GLfloat); }
		inline GLsizeiptr Size() const { return elementCount * sizeof(GLfloat); }
	};

	class Cube : public Shape {
	protected:
		void AllocateVertexData();
	public:
		Cube();


	};

};

