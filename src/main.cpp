
#include<jlg/jlg.h>
#include<jlg/callbacks.h>

void testcb(GLFWwindow* window, int key, int scancode, int action, int mode);
void testcb1(GLFWwindow* window, int key, int scancode, int action, int mode);
int main(int argc, char* argv[]) {
	jlg::Window win(800,600,"Window");
	win.SetViewport();
	win.SetColor(0.2, 0.1f, 0.1f,1.0f);
	jlg::cb_mgr::bind_context(win.Handle(), jlg::JLG_CBFUN_KEYBOARD_INPUT);
	jlg::cb_mgr::subscribe(win.Handle(), jlg::JLG_CBFUN_KEYBOARD_INPUT, testcb);
	jlg::cb_mgr::subscribe(win.Handle(), jlg::JLG_CBFUN_KEYBOARD_INPUT, testcb1);

	while (!glfwWindowShouldClose(win.Handle())) {
		glfwPollEvents();
		win.Render();
		glfwSwapBuffers(win.Handle());
	}

	return EXIT_SUCCESS;
}

void testcb(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS) {
		std::cout << "you pressed key num " << key << std::endl;
	}
}

void testcb1(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_RELEASE) {
		std::cout << "you released key num " << key << std::endl;
	}
}


