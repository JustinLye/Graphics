#pragma once
#include<vector>
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include<GL/glew.h>
#include<GLFW/glfw3.h>

namespace jlg {
	struct VertexAttribs {
		GLuint index;
		GLint size;
		GLenum type;
		GLboolean normalized;
		GLsizei stride;
		const void* pointer;
		VertexAttribs(
			GLuint Index,
			GLint Size,
			GLenum Type,
			GLboolean Normalized,
			GLsizei Stride,
			const void* Pointer) :
			index(Index),
			size(Size),
			type(Type),
			normalized(Normalized),
			stride(Stride),
			pointer(Pointer) {}
		void Enable() {
			glVertexAttribPointer(
				this->index,
				this->size,
				this->type,
				this->normalized,
				this->stride,
				this->pointer);
			glEnableVertexAttribArray(this->index);
		}
	};
	struct BufferObject {
		GLuint ID;
		GLenum target;
		GLsizeiptr dataSize;
		const void* dataSource;
		GLenum usage;
		std::vector<VertexAttribs> attribs;
		void Generate() {
			glGenBuffers(1, &this->ID);
		}
		void Bind() {
			glBindBuffer(this->target, this->ID);
			for (auto i = attribs.begin(); i != attribs.end(); ++i) {
				i->Enable();
			}
		}
	};

	struct VertexObject {
		GLuint ID;
		GLenum mode;
		GLint first;
		GLsizei count;
		BufferObject buffer;
		void Generate() {
			glGenVertexArrays(1, &this->ID);
			
		}
		void Bind() {
			glBindVertexArray(this->ID);
			buffer.Bind();
			glBindVertexArray(0);
		}
		void Draw() {
			glBindVertexArray(this->ID);
			glDrawArrays(this->mode, this->first, this->count);
			glBindVertexArray(0);
		}
	};
};
