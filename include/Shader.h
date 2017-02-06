#pragma once

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<GL/glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"freader.h"
namespace jlg {
	class shader {
	public:
		GLuint program;
		shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);
		shader();
		inline void use_program() const { 
			if (initialized) {
				glUseProgram(this->program);
			} else {
				std::cerr << "ERROR::SHADERS::INITIALIZATION::SHADER IS NOT INITIALIZED" << std::endl;
				throw;
			}
		}
		void init_shader_program(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);
		inline bool is_initialized() const { return initialized; }
		void LoadUniformMatrix4fv(const GLchar* UniformName, glm::mat4& MatrixData);
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