#include<iostream>
#include<stdexcept>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<jlg/jlgbase.h>

int main(int argc, char* argv[]) {
	jlg::Window window(1600, 1200, "Window");
	window.SetViewport();
	window.SetColor(0.15, 0.25, 0.30, 1.0f);
	jlg::camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	jlg::camera_mgr::bind_camera(&camera, window.Handle(), 1600, 1200);
	jlg::shape_mgr shapes;
	GLuint shape_id;
	jlg::add_triangle(shape_id, &shapes);
	shapes.buffer();
	while (!glfwWindowShouldClose(window.Handle())) {
		glfwPollEvents();
		window.Render();
		shapes.draw();
		glfwSwapBuffers(window.Handle());
	}
	return EXIT_SUCCESS;
}



