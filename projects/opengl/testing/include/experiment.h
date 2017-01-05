#pragma once

#include"shader.h"
#include"shapes.h"

namespace jlg {
	namespace experimental {
		class TriangleExp : public Shader, public Triangle2D {
		public:
			TriangleExp(const GLchar* VertexSourcePath, const GLchar* FragementSourcePath, const GLfloat& Center = 0.0f, const GLfloat& SideLength = 0.5f) :
				Shader(VertexSourcePath, FragementSourcePath),
				Triangle2D(Center, SideLength) {}
			virtual inline void Draw() const {
				glUseProgram(this->Program);
				glBindVertexArray(this->VAO);
				glDrawArrays(GL_TRIANGLES, 0, 3);
				glBindVertexArray(0);
			}
		};
	};

};
