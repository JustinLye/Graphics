
#include"model.h"

jlg::Model::Model() : Cube() {}

void jlg::Model::BindModel(
	const GLuint& VertexArrayObject,
	const GLuint& VertexBufferObject,
	const GLuint& ElementBufferObject,
	const GLuint& TextureID,
	const GLchar* ImageFilePath) {
	BindBuffer(VertexArrayObject, VertexBufferObject, ElementBufferObject);
	texture.imagePath = ImageFilePath;
	texture.BufferTexture(TextureID);
}

void jlg::Model::Draw() {
	
}