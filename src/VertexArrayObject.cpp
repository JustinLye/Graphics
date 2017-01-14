#include"..\include\VertexArrayObject.h"

jlg::VertexArrayObject::VertexArrayObject(const char* imagePath) : initialized(false) {
	InitializeObject(imagePath);
}

void jlg::VertexArrayObject::InitializeObject(const char* imagePath) {
	LoadShape();
	LoadTexture(imagePath);
	initialized = true;
}

void jlg::VertexArrayObject::LoadShape() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, cube.Size(), cube.VertexData(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, cube.Stride(), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, cube.Stride(), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void jlg::VertexArrayObject::LoadTexture(const char* imagePath) {
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
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

