#include<iostream>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<SOIL2/SOIL2.h>
#include"window3d.h"

GLuint WIDTH = 800, HEIGHT = 600;
GLint screenWidth, screenHeight;
const GLchar* TITLE = "OpenGL Window";

void RenderLoop(GLFWwindow* window);
void KeyPressEvent(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mode);
int main(int argc, char* argv[]) {
	jlg::Window3d window("window1");
	jlg::ViewNames* winnames = &window.viewManager.data.names;
	winnames->VertexShaderPath = "threed.vs";
	winnames->FragmentShaderPath = "threed.frag";
	winnames->TextureImagePath = "container.jpg";
	winnames->ModelUniformName = "model";
	winnames->ViewUniformName = "view";
	winnames->ProjUniformName = "projection";
	winnames->TextureUniformName = "texture0";
	//std::cout << std::boolalpha << window.viewManager.data.names.IsComplete() << std::endl;
	std::cout << window.viewManager.data.names.FragmentShaderPath << std::endl;
	window.Initialize();
	window.SetClearColor(0.3f, 0.4f, 0.3f, 1.0f);
	GLfloat deltaTime = 0.0f;
	GLfloat currentFrame = 0.0f;
	GLfloat lastFrame = 0.0f;
	glfwMakeContextCurrent(window.window());
	glfwSetInputMode(window.window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	while (window.IsActive()) {
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		window.Render(deltaTime);
	}
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