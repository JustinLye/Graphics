#include"..\include\shapes.h"

jlg::Shape::Shape(GLuint VertexDim, GLuint VertexCount) :
	vertexDim(VertexDim),
	vertexCount(VertexCount),
	elementCount(VertexDim * VertexCount),
	vertexData(nullptr) {}

jlg::Shape::~Shape() {
	if(vertexData != nullptr)
		delete[] vertexData;
}

void jlg::Shape::Scale(const GLfloat& Multiplier) {
	if(vertexData == nullptr)
		return;
	for(GLuint r = 0; r < vertexCount; r++)
		for(GLuint c = 0; c < 3; c++)
			*(vertexData + (r * vertexDim) + c) *= Multiplier;
}



void jlg::Cube::AllocateVertexData() {
	points = new GLfloat[40] {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //Bottom Back Left
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, //Bottom Front Left
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, //Bottom Back Right
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, //Bottom Front Right
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, //Top Back Left
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, //Top Front Left
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, //Top Back Right
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f  //Top Front Right
	};
	indices = new GLuint[36]{
		BOTTOM_BACK_LEFT, BOTTOM_BACK_RIGHT, TOP_BACK_RIGHT,
		TOP_BACK_RIGHT, TOP_BACK_LEFT, BOTTOM_BACK_LEFT,
		BOTTOM_FRONT_LEFT, BOTTOM_FRONT_RIGHT, TOP_FRONT_RIGHT,
		TOP_FRONT_RIGHT, TOP_FRONT_LEFT, BOTTOM_FRONT_LEFT,
		TOP_FRONT_LEFT, TOP_BACK_LEFT, BOTTOM_BACK_LEFT,
		BOTTOM_BACK_LEFT, BOTTOM_FRONT_LEFT, TOP_FRONT_LEFT,
		TOP_FRONT_RIGHT, TOP_BACK_RIGHT, BOTTOM_BACK_RIGHT,
		BOTTOM_BACK_RIGHT, BOTTOM_FRONT_RIGHT, TOP_FRONT_RIGHT,
		BOTTOM_BACK_LEFT, BOTTOM_BACK_RIGHT, BOTTOM_FRONT_RIGHT,
		BOTTOM_FRONT_RIGHT, BOTTOM_FRONT_LEFT, BOTTOM_BACK_LEFT,
		TOP_FRONT_LEFT, TOP_FRONT_RIGHT, TOP_BACK_RIGHT,
		TOP_BACK_RIGHT, TOP_BACK_LEFT, TOP_FRONT_LEFT
	};
}

jlg::Cube::Cube() : Shape(5, 8), points(nullptr), indices(nullptr), vertexArrayPtr(nullptr) {
	AllocateVertexData();
}

void jlg::Cube::BindBuffer(const GLuint& VertexArrayObject, const GLuint& VertexBufferObject, const GLuint& ElementBufferObject) {
	vertexArrayPtr = &VertexArrayObject;
	glBindVertexArray(VertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, 40 * sizeof(GLfloat), points, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLfloat), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}

void jlg::Cube::Draw() {
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}