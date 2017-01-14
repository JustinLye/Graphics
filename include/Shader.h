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
		Shader();
		inline void UseProgram() const { 
			if (initialized) {
				glUseProgram(this->Program);
			} else {
				std::cerr << "ERROR::SHADERS::INITIALIZATION::SHADER IS NOT INITIALIZED" << std::endl;
				throw;
			}
		}
		void InitializeShaderProgram(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);
	protected:
		void LoadVertexShader(const GLchar* vertexShaderSourceCode);
		void LoadFragmentShader(const GLchar* fragmentShaderSourceCode);
		void CreateProgram();
	private:
		GLuint vertexShaderID;
		GLuint fragementShaderID;
		bool initialized;
		
	};
};