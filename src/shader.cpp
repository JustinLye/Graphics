#include"jlg/base/shader.h"

jlg::shader::shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath) :
	initialized(false),
	_vertex_file_path(nullptr),
	_fragment_file_path(nullptr) {
	init_shader_program(vertexShaderPath, vertexShaderPath);
}

jlg::shader::shader() : initialized(false) {}

void jlg::shader::init_shader_program(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath) {
	initialized = false;
	_vertex_file_path = vertexShaderPath;
	_fragment_file_path = fragmentShaderPath;
	//check for existing shader files
	bool filepath_okay = true;
	if (!existing_file(_vertex_file_path)) {
		if (handle_filepath_error(_vertex_file_path)) {
			if (!resolve_filepath(JLGshader::JLG_SHADER_FILEPATH_UPDATE_VERTEX_SHADER)) {
				std::cerr << "ERROR::SHADERS::VERTEX::FAILED TO READ SOURCE" << std::endl;
				filepath_okay = false;
			}
		} else {
			std::cerr << "ERROR::SHADERS::VERTEX::FAILED TO READ SOURCE" << std::endl;
			filepath_okay = false;
		}
	}
	if (!existing_file(_fragment_file_path)) {
		if (handle_filepath_error(_fragment_file_path)) {
			if (!resolve_filepath(JLGshader::JLG_SHADER_FILEPATH_UPDATE_FRAGMENT_SHADER)) {
				std::cerr << "ERROR::SHADERS::FRAGMENT::FAILED TO READ SOURCE" << std::endl;
				filepath_okay = false;
			}
		} else {
			std::cerr << "ERROR::SHADERS::FRAGMENT::FAILED TO READ SOURCE" << std::endl;
			filepath_okay = false;
		}
	}
	if(!filepath_okay)
		return;
	bool program_compile_okay = true;
	std::string vertexShaderSourceCode;
	std::string fragmentShaderSourceCode;
	jlg::FileContentToString(_vertex_file_path, vertexShaderSourceCode);
	jlg::FileContentToString(_fragment_file_path, fragmentShaderSourceCode);
	if (vertexShaderSourceCode.empty()) {
		std::cerr << "ERROR::SHADERS::VERTEX::FAILED TO READ SOURCE" << std::endl;
		program_compile_okay = false;
	}
	if (fragmentShaderSourceCode.empty()) {
		std::cerr << "ERROR::SHADERS::FRAGMENT::FAILED TO READ SOURCE" << std::endl;
		program_compile_okay = false;
	}

	if(!this->LoadVertexShader(vertexShaderSourceCode.c_str()))
		program_compile_okay = false;
	if(!this->LoadFragmentShader(fragmentShaderSourceCode.c_str()))
		program_compile_okay = false;
	if(!this->CreateProgram())
		program_compile_okay = false;
	if(program_compile_okay)
		initialized = true;
	if (initialized) {
		std::cout << "shader was successfully initialized." << std::endl;
	} else {
		std::cout << "shader failed to be initialized." << std::endl;
	}
}

void jlg::shader::LoadUniformMatrix4fv(const GLchar* UniformName, glm::mat4& MatrixData) {
	GLuint loc = glGetUniformLocation(this->program, UniformName);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(MatrixData));
}

bool jlg::shader::LoadVertexShader(const GLchar* vertexShaderSourceCode) {
	GLint success;
	GLchar infoLog[512];
	this->vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->vertexShaderID, 1, &vertexShaderSourceCode, NULL);
	glCompileShader(this->vertexShaderID);
	glGetShaderiv(this->vertexShaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(this->vertexShaderID, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADERS::VERTEX::COMPILATION FAILED" << std::endl << infoLog << std::endl;
		return false;
	}
	return true;
}

bool jlg::shader::LoadFragmentShader(const GLchar* fragmentShaderSourceCode) {
	GLint success;
	GLchar infoLog[512];
	this->fragementShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->fragementShaderID, 1, &fragmentShaderSourceCode, NULL);
	glCompileShader(this->fragementShaderID);
	glGetShaderiv(this->fragementShaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(this->fragementShaderID, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADERS::FRAGMENT::COMPILATION FAILED" << std::endl << infoLog << std::endl;
		return false;
	}
	return true;
}

bool jlg::shader::CreateProgram() {
	GLint success;
	GLchar infoLog[512];
	bool result = true;
	this->program = glCreateProgram();
	glAttachShader(this->program, this->vertexShaderID);
	glAttachShader(this->program, this->fragementShaderID);
	glLinkProgram(this->program);
	glGetProgramiv(this->program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->program, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADERS::PROGRAM::LINK FAILED" << std::endl << infoLog << std::endl;
		result = false;
	}
	glDeleteShader(this->vertexShaderID);
	glDeleteShader(this->fragementShaderID);
	return result;
}

bool jlg::shader::handle_filepath_error(const GLchar* filepath) {
	std::cerr << filepath << " does not exist." << std::endl;
	std::cout << "Would you like to enter a different filepath? (y/n): ";
	char response = '\0';
	std::cin >> response;
	std::cin.ignore();
	std::cin.clear();
	system("cls");
	int attempt_count = 0;
	while (response != 'y' && response != 'n' && attempt_count++ <= 3) {
		std::cerr << response << " is an invalid input. Please y or n (must be lowercase)." << std::endl <<
			"Would you like to enter a different filepath? (y,n): ";
		std::cin >> response;
		std::cin.ignore();
		std::cin.clear();
		system("cls");
	}
	if(response == 'y')
		return true;
	else
		return false;
}

bool jlg::shader::resolve_filepath(JLGshader update_shader) {
	char filepath_input[5096];
	const char* filepath;
	bool resolved = false;
	std::cout << "Enter the new filepath: ";
	filepath = gets_s(filepath_input, 5096);
	system("cls");
	if (existing_file(filepath)) {
		std::cout << filepath << " is valid!" << std::endl;
		if (update_shader == JLGshader::JLG_SHADER_FILEPATH_UPDATE_VERTEX_SHADER) {
			this->_vertex_file_path = filepath;
			std::cout << "Vertex shader source file path was updated." << std::endl;
			resolved = true;
		} else if (update_shader == JLGshader::JLG_SHADER_FILEPATH_UPDATE_FRAGMENT_SHADER) {
			this->_fragment_file_path = filepath;
			std::cout << "Fragment shader source file path was updated." << std::endl;
			resolved = true;
		} else {
			std::cerr << "WARNING::SHADERS::resolve_filepath()::Unknown shader type. File path could not be resolved." << std::endl;
		}
	} else if (handle_filepath_error(filepath)) {
		return resolve_filepath(update_shader);
	} else {
		return false;
	}
	return resolved;
}