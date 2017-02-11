#include<iostream>
#include"jlg/window.h"
#include"jlg/event_manager.h"

void test_cb(GLFWwindow* window, int key, int action, int scancode, int mode);

int main(int argc, char* argv[]) {
	try {
		GLFWwindow* window = jlg::WindowContext::CreateWindow(800, 600, "Window1");
		jlg::WindowContext::CreateWindow(800, 600, "Window2");
		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, jlg::event_manager::key_callback);
		jlg::event_manager::Subscribe(window, jlg::JLG_EVENT_TYPE_KEY_INPUT, test_cb);
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
			glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glfwSwapBuffers(window);
		}
	} catch (...) {
		std::cout << "Error occurred" << std::endl;
		return EXIT_FAILURE;
	}
	glfwTerminate();
	return EXIT_SUCCESS;
}

void test_cb(GLFWwindow* window, int key, int action, int scancode, int mode) {
	std::cout << "test_cb" << std::endl;
}