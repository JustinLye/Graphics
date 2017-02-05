#include"..\include\Shader.h"

jlg::Shader::Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath) :
	initialized(false) {
	InitializeShaderProgram(vertexShaderPath, fragmentShaderPath);
}

jlg::Shader::Shader() : initialized(false) {}

void jlg::Shader::InitializeShaderProgram(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath) {
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

void jlg::Shader::LoadUniformMatrix4fv(const GLchar* UniformName, glm::mat4& MatrixData) {
	GLuint loc = glGetUniformLocation(this->Program, UniformName);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(MatrixData));
}

void jlg::Shader::LoadVertexShader(const GLchar* vertexShaderSourceCode) {
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

void jlg::Shader::LoadFragmentShader(const GLchar* fragmentShaderSourceCode) {
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

void jlg::Shader::CreateProgram() {
	GLint success;
	GLchar infoLog[512];
	this->Program = glCreateProgram();
	glAttachShader(this->Program, this->vertexShaderID);
	glAttachShader(this->Program, this->fragementShaderID);
	glLinkProgram(this->Program);
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADERS::PROGRAM::LINK FAILED" << std::endl << infoLog << std::endl;
	}
	glDeleteShader(this->vertexShaderID);
	glDeleteShader(this->fragementShaderID);

}