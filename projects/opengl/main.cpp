#include<iostream>
#include"jlg_window.h"


int main(int argc, char* argv[]) {
	jlg::AppWindow win;
	glfwMakeContextCurrent(win.Handle());
	while (!glfwWindowShouldClose(win.Handle())) {
		glfwPollEvents();
		win.ClearColorBuffer();
		glfwSwapBuffers(win.Handle());
	}
	glfwTerminate();
	return EXIT_SUCCESS;
}


