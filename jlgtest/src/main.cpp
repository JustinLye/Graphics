#include<iostream>
#include"jlg/window.h"

void kcb(GLFWwindow* window, int key, int action, int scancode, int mode);


class cb {
public:
	GLFWwindow* cb_win;
	void operator()() { std::cout << "cb call made from " << cb_win << std::endl; }
};

void CreateWindow(const GLchar* name, jlg::WindowContext* window) {
	window = new jlg::WindowContext(800, 600, name, &jlg::ClearColor(0.1f, 0.3f, 0.3f, 1.0f), GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int main(int argc, char* argv[]) {
	jlg::WindowContext* w1 = nullptr;
	std::thread t1(CreateWindow,"Window1", w1);
	t1.join();
	while (!glfwWindowShouldClose(w1->ContextHandle())) {
		glfwPollEvents();
		w1->ClearBuffer();
		glfwSwapBuffers(w1->ContextHandle());
	}
	glfwTerminate();
	delete w1;
	return EXIT_SUCCESS;
}

void kcb(GLFWwindow* window, int key, int action, int scancode, int mode) {
	cb* _tcb = nullptr;
	_tcb = (cb*)glfwGetWindowUserPointer(window);
	if (_tcb) {
		_tcb->operator()();
	}
}