#include"jlg/base/shader.h"

jlg::shader::shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath) :
	initialized(false) {
	init_shader_program(vertexShaderPath, fragmentShaderPath);
}

jlg::shader::shader() : initialized(false) {}

void jlg::shader::init_shader_program(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath) {
	initialized = false;
	std::string vertexShaderSourceCode;
	std::string fragmentShaderSourceCode;
	jlg::FileContentToString(vertexShaderPath, vertexShaderSourceCode);
	jlg::FileContentToString(fragmentShaderPath, fragmentShaderSourceCode);
	if (vertexShaderSourceCode.empty()) {
		std::cerr << "ERROR::SHADERS::VERTEX::FAILED TO READ SOURCE" << std::endl;
	}
	if (fragmentShaderSourceCode.empty()) {
		std::cerr << "ERROR::SHADERS::FRAGMENT::FAILED TO READ SOURCE" << std::endl;
	}

	this->LoadVertexShader(vertexShaderSourceCode.c_str());
	this->LoadFragmentShader(fragmentShaderSourceCode.c_str());
	this->CreateProgram();
	initialized = true;
}

void jlg::shader::LoadUniformMatrix4fv(const GLchar* UniformName, glm::mat4& MatrixData) {
	GLuint loc = glGetUniformLocation(this->program, UniformName);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(MatrixData));
}

void jlg::shader::LoadVertexShader(const GLchar* vertexShaderSourceCode) {
	GLint success;
	GLchar infoLog[512];
	this->vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->vertexShaderID, 1, &vertexShaderSourceCode, NULL);
	glCompileShader(this->vertexShaderID);
	glGetShaderiv(this->vertexShaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(this->vertexShaderID, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADERS::VERTEX::COMPILATION FAILED" << std::endl << infoLog << std::endl;
	}
}

void jlg::shader::LoadFragmentShader(const GLchar* fragmentShaderSourceCode) {
	GLint success;
	GLchar infoLog[512];
	this->fragementShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->fragementShaderID, 1, &fragmentShaderSourceCode, NULL);
	glCompileShader(this->fragementShaderID);
	glGetShaderiv(this->fragementShaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(this->fragementShaderID, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADERS::FRAGMENT::COMPILATION FAILED" << std::endl << infoLog << std::endl;
	}
}

void jlg::shader::CreateProgram() {
	GLint success;
	GLchar infoLog[512];
	this->program = glCreateProgram();
	glAttachShader(this->program, this->vertexShaderID);
	glAttachShader(this->program, this->fragementShaderID);
	glLinkProgram(this->program);
	glGetProgramiv(this->program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->program, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADERS::PROGRAM::LINK FAILED" << std::endl << infoLog << std::endl;
	}
	glDeleteShader(this->vertexShaderID);
	glDeleteShader(this->fragementShaderID);

}