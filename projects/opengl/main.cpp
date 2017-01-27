#include<iostream>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"jlg_window.h"
#include"shape.h"
#include"Shader.h"
int main(int argc, char* argv[]) {
    jlg::Window win(800,600,"Window");
	win.SetViewport();

	jlg::Shader shader("core.vs", "core.frag");
	
	GLfloat verts[] = {
		0.5f, 0.5f, 0.0f,
		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};
	jlg::shape triangle(verts, 3, 3);
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	triangle.add_attrib(3);
	triangle.buffer(VAO, VBO);

	//glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, triangle.vertex_size(), triangle.vertices(), GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	//glEnableVertexAttribArray(0);
	//glBindVertexArray(0);

	while (!glfwWindowShouldClose(win.Handle())) {
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.UseProgram();
		glBindVertexArray(VAO);
		triangle.draw();
		glBindVertexArray(0);
		glfwSwapBuffers(win.Handle());
	}
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
	glfwTerminate();
	return EXIT_SUCCESS;
}


