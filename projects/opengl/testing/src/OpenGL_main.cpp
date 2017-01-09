#include<iostream>
#include<vector>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<SOIL2.h>

#include"shapes.h"
#include"shader.h"
#include"experiment.h"
#include"camera.h"
#include"texture.h"
GLuint WIDTH = 800, HEIGHT = 600;
GLint screenWidth, screenHeight;
const GLchar* TITLE = "OpenGL Window";

void RenderWindow(GLFWwindow* window, const jlg::shapes::Shape& shape, jlg::Shader& shader, GLuint texture, GLuint VAO, GLfloat screenWidth, GLfloat screenHeight);
void KeyPressEvent(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mode);
void MouseMoveEvent(GLFWwindow* window, double xpos, double ypos);
void MouseScrollEvent(GLFWwindow* window, double xoffset, double yoffset);
void DoMovement();
bool keys[1024];
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
GLboolean firstMouse = true;
GLfloat lastX = 400.0f;
GLfloat lastY = 300.0f;
jlg::Camera camera(glm::vec3(0.0f, 0.0f,3.0f));
int main(int argc, char* argv[]) {
	//initalize GLFW
	glfwInit();
	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);
	if (window == nullptr) {
		std::cerr << "ERROR::INITILIZATION::WINDOW::FAILED TO CREATE WINDOW" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "ERROR::INITILIZATION::EXTENSION WRANGLER::FAILED TO INITIALIZE" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwSetKeyCallback(window, KeyPressEvent);
	glfwSetCursorPosCallback(window, MouseMoveEvent);
	glfwSetScrollCallback(window, MouseScrollEvent);
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glViewport(0, 0, screenWidth, screenHeight);
	glEnable(GL_DEPTH_TEST);
	jlg::shapes::Cube cube;
	GLuint texture1, VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 180 * sizeof(GLfloat), cube.Data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("images/container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	jlg::Shader shader("shaders/cube.vs", "shaders/cube.frag");
	RenderWindow(window, cube, shader, texture1, VAO, screenWidth, screenHeight);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	
	return EXIT_SUCCESS;
}


void RenderWindow(GLFWwindow* window, const jlg::shapes::Shape& shape,  jlg::Shader& shader, GLuint texture, GLuint VAO, GLfloat screenWidth, GLfloat screenHeight) {

	while (!glfwWindowShouldClose(window)) {
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();
		DoMovement();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.UseProgram();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(shader.Program, "texture1"),0);
		glm::mat4 view;
		view = camera.GetViewMatrix();
		glm::mat4 projection;
		projection = glm::perspective(camera.GetZoom(), (float)screenWidth/(float)screenHeight, 0.1f, 1000.0f);
		GLint modelLoc = glGetUniformLocation(shader.Program, "model");
		GLint viewLoc = glGetUniformLocation(shader.Program, "view");
		GLint projLoc = glGetUniformLocation(shader.Program, "projection");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glBindVertexArray(VAO);
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 20.0f, glm::vec3(1.0f, 0.3f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

}

void DoMovement() {
	if(keys[GLFW_KEY_W])
		camera.ProcessKeyboard(jlg::FORWARD, deltaTime);
	if(keys[GLFW_KEY_S])
		camera.ProcessKeyboard(jlg::BACK, deltaTime);
	if(keys[GLFW_KEY_A])
		camera.ProcessKeyboard(jlg::LEFT, deltaTime);
	if(keys[GLFW_KEY_D])
		camera.ProcessKeyboard(jlg::RIGHT, deltaTime);
}

void KeyPressEvent(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mode) {
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key <= 1024) {
		if (action == GLFW_PRESS) {
			keys[key] = true;
		} else if (action == GLFW_RELEASE) {
			keys[key] = false;
		}
	}
}

void MouseMoveEvent(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;
	camera.ProcessMouseMovement(xoffset, yoffset);
}

void MouseScrollEvent(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}