#include"window3d.h"
jlg::Window3d* jlg::CallBackWrapper::winView = nullptr;

void jlg::CallBackWrapper::BindCallBackEvents(Window3d* window) {
	window->SetCallback(KeyPressEvent);
	window->SetCallback(MouseMoveEvent);
	window->SetCallback(MouseScrollEvent, WIN_CALLBACK_SCROLL_FUN);
}

void jlg::CallBackWrapper::KeyPressEvent(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(winView->window(), GLFW_TRUE);
	if (key >= 0 && key < 1024) {
		if(action == GLFW_PRESS)
			winView->viewManager.data.keys[key] = true;
		else if(action == GLFW_RELEASE)
			winView->viewManager.data.keys[key] = false;
	}
	if (key == GLFW_KEY_LEFT_SHIFT) {
		if (action == GLFW_PRESS) {
			winView->viewManager.camera.Boost = 4.0f;
		} else if(action == GLFW_RELEASE)
			winView->viewManager.camera.Boost = 1.0f;
	}

}

void jlg::CallBackWrapper::MouseMoveEvent(GLFWwindow* window, double xpos, double ypos) {
	if (winView->firstMouse) {
		winView->lastX = xpos;
		winView->lastY = ypos;
		winView->firstMouse = false;
	}

	GLfloat xoffset = xpos - winView->lastX;
	GLfloat yoffset = winView->lastY - ypos;

	winView->lastX = xpos;
	winView->lastY = ypos;

	winView->viewManager.camera.ProcessMouseMovement(xoffset, yoffset);
}

void jlg::CallBackWrapper::MouseScrollEvent(GLFWwindow* window, double xoffset, double yoffset) {
	winView->viewManager.camera.ProcessMouseScroll(yoffset);
}

void jlg::CallBackWrapper::DoMovement() {
	if (winView->viewManager.data.keys[GLFW_KEY_W])
		winView->viewManager.camera.ProcessKeyboard(FORWARD, winView->deltaTime);
	if (winView->viewManager.data.keys[GLFW_KEY_S])
		winView->viewManager.camera.ProcessKeyboard(BACKWARD, winView->deltaTime);
	if (winView->viewManager.data.keys[GLFW_KEY_A])
		winView->viewManager.camera.ProcessKeyboard(LEFT, winView->deltaTime);
	if (winView->viewManager.data.keys[GLFW_KEY_D])
		winView->viewManager.camera.ProcessKeyboard(RIGHT, winView->deltaTime);
	
}

void jlg::CallBackWrapper::HandleCallBackEvents(Window3d* window, bool ManageContext) {
	SetCurrentWindow(window);
	if (ManageContext) {
		GLFWwindow* origWindow = glfwGetCurrentContext();
		glfwMakeContextCurrent(winView->window());
		DoMovement();
		glfwPollEvents();
		
		glfwMakeContextCurrent(origWindow);
	} else {
		DoMovement();
		glfwPollEvents();
		
	}
	SetCurrentWindow(nullptr);
}

void jlg::Window3d::Render(GLfloat DeltaTime) {
	deltaTime = DeltaTime;
	CallBackWrapper::HandleCallBackEvents(this);
	//check if window should close. If true then destroy the window and return immediately
	if (glfwWindowShouldClose(winPtr)) {
		if (winPtr == glfwGetCurrentContext()) {
			Destroy();
			glfwMakeContextCurrent(NULL);
			return;
		} else {
			Destroy();
			return;
		}
	}
	////DoMovement();
	glClearColor(info.clearColor.r, info.clearColor.g, info.clearColor.b, info.clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//shader.UseProgram();
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, vao.texID);
	//glUniform1i(glGetUniformLocation(shader.Program, "texture0"),0);
	////glBindTexture(GL_TEXTURE_2D, 0);
	//glm::mat4 view;
	//view = camera.GetViewMatrix();
	//glm::mat4 projection;
	//projection = glm::perspective(camera.Zoom, (float)info.width/(float)info.height, .01f, 1000.0f);
	//GLuint modelLoc = glGetUniformLocation(shader.Program, "model");
	//GLuint viewLoc = glGetUniformLocation(shader.Program, "view");
	//GLuint projLoc = glGetUniformLocation(shader.Program, "projection");
	//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	//glBindVertexArray(vao.VAO);
	//glm::mat4 model;
	//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	//model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.3f, 0.5f));
	//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//glDrawArrays(GL_TRIANGLES, 0, vao.cube.VertexCount());
	//glBindVertexArray(0);
	viewManager.UpdateView();
	glfwSwapBuffers(winPtr);
}

//void jlg::Window3d::LoadShader(const char* vertexShaderPath, const char* fragmentShaderPath) {
//	shader.InitializeShaderProgram(vertexShaderPath, fragmentShaderPath);
//}
//
//void jlg::Window3d::LoadVertexArrayObject(const char* imagePath) {
//	vao.InitializeObject(imagePath);
//}

void jlg::Window3d::SetCallbacks() {
	CallBackWrapper::BindCallBackEvents(this);
}

void jlg::Window3d::Initialize() {
	if(!IsCreated())
		Create();
	glfwMakeContextCurrent(winPtr);
	SetCallbacks();
	deltaTime = 0.0f;
	lastFrame = 0.0f;
	viewManager.Initialize();
}


