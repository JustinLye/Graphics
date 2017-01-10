#include<iostream>
#include<vector>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<SOIL2.h>

#include"window.h"
GLuint WIDTH = 800, HEIGHT = 600;
GLint screenWidth, screenHeight;
const GLchar* TITLE = "OpenGL Window";

void RenderLoop(jlg::WinGroup* windows);
bool AllWindowsShouldClose(int count, jlg::Window* windows);
void KeyPressEvent(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mode);
void WindowClose(GLFWwindow* window);
void PrintError(int error, const char* description);
int main(int argc, char* argv[]) {
	jlg::WinGroup windowGroup;
	windowGroup.PushBack();
	windowGroup.PushBack();
	
	windowGroup.SetCallback(KeyPressEvent);
	RenderLoop(&windowGroup);

	glfwTerminate();
	return EXIT_SUCCESS;
}


void RenderLoop(jlg::WinGroup* windows) {
	while (windows->IsActive()) {
		windows->Render();
	}
}

bool AllWindowsShouldClose(int count, jlg::Window* windows) {
	for (int i = 0; i < count; i++)
		if(windows[i].IsActive())
			return false;
	return true;
}

void KeyPressEvent(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		std::cout << "escape key press" << std::endl;
		glfwSetWindowShouldClose(window, GL_TRUE);
		glfwHideWindow(window);
		
	}
}

void WindowClose(GLFWwindow* window) {
	std::cout << "a window is to close" << std::endl;
	glfwHideWindow(window);
}

void PrintError(int error, const char* description) {
	std::cerr << error << '\t' << description << std::endl;
}