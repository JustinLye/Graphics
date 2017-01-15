#include"texture.h"

jlg::Texture::Texture() :
	imagePath(nullptr),
	uniformName(nullptr) {}

jlg::Texture::Texture(const char* ImageFilePath, const char* UniformName) :
	imagePath(ImageFilePath),
	uniformName(UniformName) {}

void jlg::Texture::BufferTexture(const GLuint& TextureID) {
	if (imagePath == nullptr) {
		std::cerr << "ERROR::TEXTURE::BUFFER TEXTURE::Image file path is NULL" << std::endl;
		throw;
	}
	texID = &TextureID;
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image(imagePath, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}