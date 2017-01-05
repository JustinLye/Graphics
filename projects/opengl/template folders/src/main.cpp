#include<iostream>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<SOIL2.h>
GLuint WIDTH = 800, HEIGHT = 600;
GLint screenWidth, screenHeight;
const GLchar* TITLE = "OpenGL Window";

void RenderLoop(GLFWwindow* window);
void KeyPressEvent(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mode);
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
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glViewport(0, 0, screenWidth, screenHeight);
	glEnable(GL_DEPTH_TEST);
	RenderLoop(window);

	glfwTerminate();
	return EXIT_SUCCESS;
}


void RenderLoop(GLFWwindow* window) {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.3f, 00.5f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(window);
	}
}

void KeyPressEvent(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mode) {
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}