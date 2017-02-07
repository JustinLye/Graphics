#pragma once

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<GL/glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"jlg/base/freader.h"
namespace jlg {
	enum JLGshader {
		JLG_SHADER_FILEPATH_UPDATE_VERTEX_SHADER = 0,
		JLG_SHADER_FILEPATH_UPDATE_FRAGMENT_SHADER = 1
	};
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
		bool LoadVertexShader(const GLchar* vertexShaderSourceCode);
		bool LoadFragmentShader(const GLchar* fragmentShaderSourceCode);
		bool CreateProgram();
	private:
		GLuint vertexShaderID;
		GLuint fragementShaderID;
		bool initialized;
		bool handle_filepath_error(const GLchar* filepath);
		bool resolve_filepath(JLGshader update_shader);
		const char* _vertex_file_path;
		const char* _fragment_file_path;

		
	};
};