#pragma once
#include<iostream>
#include<vector>
#include<GLFW/glfw3.h>
#include"shader.h"
namespace jlg {
	namespace shapes {
		class Shape {
		public:
			inline GLsizeiptr Size() const { return vertexCount * 3 * sizeof(GLfloat); }
			inline GLint VertexCount() const { return vertexCount; }
			const GLfloat* Data() const { return vertices; }
		protected:
			GLint vertexCount;
			GLfloat firstVertex;
			GLfloat* vertices;
			GLsizeiptr size;
			virtual void AllocateVertices() = 0;
		};

		class Triangle2D : public Shape {
		protected:
			GLfloat center;
			GLfloat sideLength;
			virtual void AllocateVertices() {
				this->vertices = new GLfloat[9]{ //deallocated in class destructor
					center-sideLength, center-sideLength, 0.0f,
					center, center+sideLength, 0.0f,
					center+sideLength, center-sideLength, 0.0f
				};
			}
		public:
			Triangle2D(const GLfloat& Center = 0.0f, const GLfloat& SideLength = 0.5f) :
				center(Center), sideLength(abs(abs(Center) - SideLength)) {
				this->vertexCount = 3;
				this->firstVertex = 0;
				this->size = 9 * sizeof(GLfloat);
				AllocateVertices();
			}
			~Triangle2D() {
				delete[] vertices;
			}
			virtual inline void Buffer(GLuint& VBO) {
				glGenBuffers(1, &VBO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER, this->Size(), this->vertices, GL_STATIC_DRAW);
				glVertexAttribPointer(0, this->vertexCount, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
				glEnableVertexAttribArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
			virtual inline void Buffer(GLuint& VAO, GLuint& VBO) {
				glGenVertexArrays(1, &VAO);
				glBindVertexArray(VAO);
				glGenBuffers(1, &VBO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER, this->Size(), this->vertices, GL_STATIC_DRAW);
				glVertexAttribPointer(0, this->vertexCount, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
				glEnableVertexAttribArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);
			}
		};
	};

	class Triangle2D {
	protected:
		GLuint VAO;
		GLuint VBO;
		shapes::Triangle2D triangle;
	public:
		Triangle2D(const GLfloat& Center = 0.0f, const GLfloat& SideLength = 0.5f) :
			triangle(Center, SideLength) {
			this->triangle.Buffer(this->VAO, this->VBO);
		}
		virtual inline void Draw() const {
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
		}
		~Triangle2D() {
			glDeleteVertexArrays(1, &this->VAO);
			glDeleteBuffers(1, &this->VBO);
		}
	};

	class Triangle : public Shader, public Triangle2D {
	public:
		Triangle(const GLchar* VertexSourcePath, const GLchar* FragementSourcePath, const GLfloat& Center = 0.0f, const GLfloat& SideLength = 0.5f) :
			Shader(VertexSourcePath, FragementSourcePath),
			Triangle2D(Center, SideLength) {}
		virtual inline void Draw() const {
			glUseProgram(this->Program);
			glBindVertexArray(this->VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
		}
	};

	class Triangles {
	protected:
		Triangle** triangles;
		GLuint size;
		GLuint capcity;
		GLboolean warningDelivered;
		void Resize() {
			Triangle** temp = triangles;
			capcity = capcity * 2;
			triangles = new Triangle*[capcity];
			for (GLuint i = 0; i < size; i++) {
				triangles[i] = temp[i];
			}
			delete[] temp;
		}
		
	public:
		Triangles(GLuint Capacity = 128) : triangles(nullptr), size(0), capcity(Capacity), warningDelivered(false) {
			if (capcity > MAX_CAPACITY) {
				std::cerr << "ERROR::TRIANGLES::CONSTRUCTOR::INIT CAPCITY IS > MAX CAPACTIY" << std::endl;
				throw std::exception("ERROR::TRIANGLES::CONSTRUCTOR::INIT CAPCITY IS > MAX CAPACTIY");
			}
			triangles = new Triangle*[capcity];
		}
		void push_back(const GLchar* vectorShaderPath, const GLchar* fragmentShaderPath, const GLfloat& Center = 0.0f, const GLfloat& SideLength = 0.5f) {
			if (capcity >= MAX_CAPACITY) {
				if(!warningDelivered)
					std::cerr << "WARNING::TRIANGLES::CAPACITY LIMIT REACHED" << std::endl;
				return;
			}
			if (size - 1 >= capcity) {
				Resize();
			}
			Triangle* temp = new Triangle(vectorShaderPath, fragmentShaderPath, Center, SideLength);
			triangles[size] = temp;
			size++;
		}
		static const GLuint MAX_CAPACITY = 1024;
		GLuint Size() const { return size; }
		GLuint Capacity() const { return capcity; }
		const Triangle* operator[](const GLuint& index) { return triangles[size]; }
		void Draw() const {
			for (GLuint i = 0; i < size; i++) {
				triangles[i]->Draw();
			}
		}
		~Triangles() {
			for (GLuint i = 0; i < size; i++)
				delete triangles[i];
			delete[] triangles;
		}
	};

	namespace shapes {
		class Cube : public Shape {
		protected:
			void AllocateVertices() {
				this->vertices = new GLfloat[180]{
					-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
					0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
					0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
					0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
					-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
					-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

					-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
					0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
					0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
					0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
					-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
					-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

					-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
					-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
					-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
					-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
					-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
					-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

					0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
					0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
					0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
					0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
					0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
					0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

					-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
					0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
					0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
					0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
					-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
					-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

					-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
					0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
					0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
					0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
					-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
					-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
				};
			}
		public:
			Cube() {
				this->vertexCount = 36;
				this->firstVertex = 0;
				this->size = 180 * sizeof(GLfloat);
				AllocateVertices();
			}
		};
	};

	struct AttribInfo {
		GLuint index;
		GLint size;
		GLenum type;
		GLboolean normalized;
		GLsizei stride;
		const void* pointer;
	};

	void Buffer(GLuint& VAO, GLuint& VBO, shapes::Shape& shape, std::vector<AttribInfo*>* attribs = nullptr) {
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, shape.Size(), shape.Data(), GL_STATIC_DRAW);
		if (attribs == nullptr) { //default is to add location attrib
			glVertexAttribPointer(0, shape.VertexCount(), GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);
		} else {
			for (int i = 0; i < attribs->size(); i++) {
				glVertexAttribPointer(
					attribs->operator[](i)->index,
					attribs->operator[](i)->size,
					attribs->operator[](i)->type,
					attribs->operator[](i)->normalized,
					attribs->operator[](i)->stride,
					attribs->operator[](i)->pointer);
				glEnableVertexAttribArray(attribs->operator[](i)->index);
			}
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
};

