#include<iostream>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"window.h"
#include"shape_mgr.h"
#include"texture_shader.h"
#include"camera_mgr.h"

jlg::camera_mgr camera;
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseMoveCallBack(GLFWwindow* window, double xpos, double ypos);
void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

int main(int argc, char* argv[]) {
	jlg::Window win(800, 600, "Window");
	win.SetViewport();
	jlg::shape_mgr shapes;
	jlg::texture_shader shader("core.vs","core.frag");
	camera.set_program_id(shader.program());
	win.SetColor(0.2f, 0.3f, 0.3f, 1.0f);
	
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
	
	glfwSetKeyCallback(win.Handle(), KeyCallback);
	glfwSetCursorPosCallback(win.Handle(), MouseMoveCallBack);
	glfwSetScrollCallback(win.Handle(), MouseScrollCallback);
	GLfloat delta_time = 0.0f;
	GLfloat last_frame = 0.0f;
	while (!glfwWindowShouldClose(win.Handle())) {
		GLfloat current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		last_frame = current_frame;
		glfwPollEvents();
		camera.do_movement(delta_time);
		win.Render();
		shader.apply();
		camera.update_mvp();
		shapes.draw();
		glfwSwapBuffers(win.Handle());
	}
	glfwTerminate();
	return EXIT_SUCCESS;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS)
			camera.keys[key] = true;
		else if (action == GLFW_RELEASE)
			camera.keys[key] = false;
	}
}
void MouseMoveCallBack(GLFWwindow* window, double xpos, double ypos) {
	if (camera.first_mouse) {
		camera.last_x = xpos;
		camera.last_y = ypos;
		camera.first_mouse = false;
	}

	GLfloat xoffset = xpos - camera.last_x;
	GLfloat yoffset = camera.last_y - ypos;
	camera.last_x = xpos;
	camera.last_y = ypos;
	camera.process_mouse_movement(xoffset, yoffset);

}
void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.process_scroll(yoffset);
}
