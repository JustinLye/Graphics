#include<iostream>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"viewer.h"
int main(int argc, char* argv[]) {
	jlg::viewer win_view(
		800,
		600,
		"Window",
		"core.vs",
		"core.frag");
 
	GLfloat verts[] = {
		0.5f, 0.5f, 0.0f,
		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	GLfloat verts2[] = {
		-0.5f, -0.5f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f
	};

	GLuint shape_id;
	GLuint shape2_id;
	win_view.gen_shape(shape_id, verts, 3, 3);
	win_view.add_shape_attrib(shape_id, 3);
	win_view.gen_shape(shape2_id, verts2, 3, 3);
	win_view.add_shape_attrib(shape2_id, 3);
	win_view.set_window_background_color(0.2f, 0.3f, 0.3f, 1.0f);
	win_view.buffer();

	while (!win_view.should_close()) {
		glfwPollEvents();
		win_view.update();
	}
	glfwTerminate();
	return EXIT_SUCCESS;
}


