#pragma once


#include<iostream>
#include<fstream>
#include<string>
#include<sstream>


#include<GL/glew.h>


namespace jml {
	class ShaderProgram {
	public:
		
		ShaderProgram(const GLchar* vertexShaderFilePath, const GLchar* fragShaderFilePath) {
			std::string vertexCode, fragCode;
			const GLchar* vertexSource;
			const GLchar* fragSource;
			std::ifstream vertexFile;
			std::ifstream fragFile;
			std::stringstream vertexStream;
			std::stringstream fragStream;
			GLuint vertexShader, fragShader;
			vertexFile.exceptions(std::iostream::badbit);
			fragFile.exceptions(std::iostream::badbit);
			try {
				vertexFile.open(vertexShaderFilePath);
				fragFile.open(fragShaderFilePath);
				if(!vertexFile.good() && fragFile.good())
					throw;
				vertexStream << vertexFile.rdbuf();
				fragStream << fragFile.rdbuf();
				vertexCode = vertexStream.str();
				fragCode = fragStream.str();
				vertexSource = vertexCode.c_str();
				fragSource = fragCode.c_str();
				vertexFile.close();
				fragFile.close();
			} catch (std::ifstream::failure& e) {
				std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n" << e.what() << std::endl;
			}

			vertexShader = glCreateShader(GL_VERTEX_SHADER);
			fragShader = glCreateShader(GL_FRAGMENT_SHADER);
			Program = glCreateProgram();
			glShaderSource(vertexShader, 1, &vertexSource, NULL);
			glShaderSource(fragShader, 1, &fragSource, NULL);
			glCompileShader(vertexShader);
			glCompileShader(fragShader);
			if(!CheckShaderCompilation(vertexShader) || !CheckShaderCompilation(fragShader))
				throw;
			glAttachShader(Program, vertexShader);
			glAttachShader(Program, fragShader);
			glLinkProgram(Program);
			glDeleteShader(vertexShader);
			glDeleteShader(fragShader);
			glLinkProgram(Program);
			if(!CheckShaderLinking(Program))
				throw;
		}
		void Use() { glUseProgram(this->Program); }
		GLuint Program;
		
	protected:
		
		bool CheckShaderCompilation(GLuint shader) {
			GLint success;
			GLchar infoLog[512];
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 512, NULL, infoLog);
				std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
				return false;
			} else {
				return true;
			}
		}

		bool CheckShaderLinking(GLuint program) {
			GLint success;
			GLchar infoLog[512];
			glGetProgramiv(program, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(program, 512, NULL, infoLog);
				std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
				return false;
			} else {
				return true;
			}
		}
	};
};