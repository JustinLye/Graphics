#include<iostream>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"window.h"
#include"shape_mgr.h"
#include"shading_mgr.h"

int main(int argc, char* argv[]) {
	jlg::Window win(800, 600, "Window");
	win.SetViewport();
	jlg::shape_mgr shapes;
	jlg::basic_shading_mgr shader("core.vs","core.frag");
	win.SetColor(0.2f, 0.3f, 0.3f, 1.0f);
	jlg::camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	jlg::camera_mgr::bind_camera(&camera, win.Handle());
	jlg::camera_mgr::bind_camera(&camera, win.Handle());
	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat cube_obj[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	GLuint shape_id;
	shapes.gen_shape(shape_id, cube_obj, 5, 36);
	shapes.add_shape_attrib(shape_id, 3);
	shapes.add_shape_attrib(shape_id, 2);
	shapes.buffer();

	shader.add_texture("container.jpg","texture_01");
	
	GLfloat delta_time = 0.0f;
	GLfloat last_frame = 0.0f;
	while (!glfwWindowShouldClose(win.Handle())) {
		GLfloat current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		last_frame = current_frame;
		glfwPollEvents();
		jlg::camera_mgr::do_movement(delta_time);
		win.Render();
		shader.apply();
		shapes.draw();
		glfwSwapBuffers(win.Handle());
	}
	glfwTerminate();
	return EXIT_SUCCESS;
}

