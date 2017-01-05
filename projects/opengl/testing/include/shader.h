#pragma once

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<GL/glew.h>
#include"freader.h"
namespace jlg {
	class Shader {
	public:
		GLuint Program;
		Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);
		inline void UseProgram() const { glUseProgram(this->Program); }
	protected:
		void LoadVertexShader(const GLchar* vertexShaderSourceCode);
		void LoadFragmentShader(const GLchar* fragmentShaderSourceCode);
		void CreateProgram();
	private:
		GLuint vertexShaderID;
		GLuint fragementShaderID;
	};
};