#include"window.h"

bool jlg::Window::isInitialized = false;

void jlg::Window::Initialize() {
	//initalize GLFW
	glfwInit();
	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	isInitialized = true;
}

GLFWwindow* jlg::Window::Create(int Width, int Height, const char* Title) {
	if (created) {
		std::cerr << "ERROR::WINDOW::CREATE::A window can only be created once." << std::endl;
		return nullptr;
	}
	if (Width > 0)
		info.width = Width;
	if (Height > 0)
		info.height = Height;
	if (Title != nullptr)
		info.title = Title;
	if (!isInitialized) {
		Initialize();
		winPtr = glfwCreateWindow(
			info.width, info.height, info.title, nullptr, nullptr);
		if (winPtr != nullptr) {
			created = true;
			MakeCurrent();
			glewExperimental = GL_TRUE;
			if (glewInit() != GLEW_OK) {
				std::cerr << "ERROR::INITILIZATION::EXTENSION WRANGLER::FAILED TO INITIALIZE" << std::endl;
				glfwTerminate();
			}
			SetViewPort();
			glEnable(GL_DEPTH_TEST);
			return winPtr;
		} else {
			created = false;
			return nullptr;
		}
	} else {
		winPtr = glfwCreateWindow(
			info.width, info.height, info.title, nullptr, nullptr);
		if (winPtr != nullptr) {
			created = true;
			return winPtr;
		} else {
			created = false;
			return nullptr;
		}
	}
}

void jlg::Window::ForceClose() {
	if (created)
		glfwSetWindowShouldClose(winPtr, GLFW_TRUE);
	else
		std::cerr << "ERROR::WINDOW::FORCE CLOSE::A window that has not been created cannot be force closed." << std::endl;
}

void jlg::Window::MakeCurrent() {
	if(created)
		glfwMakeContextCurrent(winPtr);
	else
		std::cerr << "ERROR::WINDOW::MAKE CURRENT::A window must be created before making it the current gl context." << std::endl;
}

void jlg::Window::SetViewPort(GLuint x, GLuint y) {
	if (!created) {
		std::cerr << "ERROR::WINDOW::SET VIEW PORT::Create the window before setting the viewport" << std::endl;
		return;
	}

	int tempWidth, tempHeight;
	glfwGetFramebufferSize(winPtr, &tempWidth, &tempHeight);
	glViewport(x,y,tempWidth, tempHeight);
}