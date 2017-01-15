#include"ViewManager.h"

jlg::ViewManager::ViewManager() : camera(glm::vec3(0.0f, 0.0f, 3.0f)) {}

jlg::ViewManager::ViewManager(const ViewNames& Names) : camera(glm::vec3(0.0f, 0.0f, 3.0f)) {
	data.names = Names;
}

void jlg::ViewManager::GenerateBuffers() {
	glGenVertexArrays(1, &data.IDs.VAO);
	glGenBuffers(1, &data.IDs.VBO);
	glGenBuffers(1, &data.IDs.EBO);
	glGenTextures(1, &data.IDs.TexID);
}

void jlg::ViewManager::BindData() {
	cube.BindBuffer(data.IDs.VAO, data.IDs.VBO, data.IDs.EBO);
	texture.BufferTexture(data.IDs.TexID);
}

void jlg::ViewManager::Initialize() {
	//if (!data.names.IsComplete()) {
	//	std::cerr << "ERROR::VIEW MANAGER::INITIALIZE::View name information is incomplete." << std::endl;
	//	throw;
	//}
	shader.InitializeShaderProgram(data.names.VertexShaderPath, data.names.FragmentShaderPath);
	texture.imagePath = data.names.TextureImagePath;
	texture.uniformName = data.names.TextureUniformName;
	GenerateBuffers();
	BindData();
}
