#include"window3d.h"

void jlg::Window3d::Render() {

}

void jlg::Window3d::LoadShader(const char* vertexShaderPath, const char* fragmentShaderPath) {
	shader.InitializeShaderProgram(vertexShaderPath, fragmentShaderPath);
}