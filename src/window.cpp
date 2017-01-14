#include"window.h"

namespace jlg {
	const char* DefaultWinTitles[] = {
		"Window 1",
		"Window 2",
		"Window 3",
		"Window 4",
		"Window 5",
		"Window 6",
		"Window 7",
		"Window 8",
		"Window 9",
		"Window 10"
	};
};
//window class
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

void jlg::Window::SetCallback(GLFWkeyfun cbfun) {
	glfwSetKeyCallback(winPtr, cbfun);
}

void jlg::Window::SetCallback(GLFWwindowclosefun cbfun) {
	glfwSetWindowCloseCallback(winPtr, cbfun);
}

void jlg::Window::Destroy() {
	if (!created) {
		std::cerr << "ERROR::WINDOW::DESTROY::A window must be created before it is destroyed" << std::endl;
		return;
	} else if (destroyed) {
		return;
	}
	glfwDestroyWindow(winPtr);
	destroyed = true;
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

void jlg::Window::Render() {
	glClearColor(info.clearColor.r, info.clearColor.g, info.clearColor.b, info.clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSwapBuffers(winPtr);
}

//WinGroup class
const int jlg::WinGroup::MAX_WINDOWS = 10;
const char* jlg::WinGroup::MAX_WINDOWS_REACHED = "ERROR::WINGROUP::PUSHBACK::Maximum windows reached";

void jlg::WinGroup::AtCapMsg() const {
	std::cerr << MAX_WINDOWS_REACHED << std::endl;
}

void jlg::WinGroup::InsertNewWindow(int Width, int Height, const char* Title) {
	if(Width <= 0)
		Width = (int)WIN_DEFAULT_WIDTH;
	if(Height <= 0)
		Height = (int)WIN_DEFAULT_HEIGHT;
	if (Title == nullptr)
		Title = DefaultWinTitles[size];
	windows[size] = Window(Width, Height, Title);
	windows[size].Create();
	size++;
}

jlg::WinGroup::WinGroup() : size(0), currContext(nullptr), windows(nullptr) {
	windows = new Window[MAX_WINDOWS];
}

jlg::WinGroup::~WinGroup() {
	delete[] windows;
}

void jlg::WinGroup::PushBack() {
	if (AtCapacity()) {
		AtCapMsg();
		return;
	}
	InsertNewWindow();
}
void jlg::WinGroup::PushBack(int Width) {
	if (AtCapacity()) {
		AtCapMsg();
		return;
	}
	InsertNewWindow(Width);
}
void jlg::WinGroup::PushBack(int Width, int Height) {
	if (AtCapacity()) {
		AtCapMsg();
		return;
	}
	InsertNewWindow(Width, Height);
}
void jlg::WinGroup::PushBack(int Width, int Height, const char* Title) {
	if (AtCapacity()) {
		AtCapMsg();
		return;
	}
	InsertNewWindow(Width, Height, Title);
}
void jlg::WinGroup::PushBack(const char* Title) {
	if (AtCapacity()) {
		AtCapMsg();
		return;
	}
	InsertNewWindow(-1,-1,Title);
}

void jlg::WinGroup::RenderAll() {
	GLFWwindow* currContext = glfwGetCurrentContext();
	for (int i = 0; i < size; i++) {
		if (windows[i].IsActive()) {
			GLFWwindow* workingWindow = windows[i].window();
			glfwMakeContextCurrent(workingWindow);
			windows[i].Render();
			glfwPollEvents();
			if (glfwWindowShouldClose(workingWindow)) {
				if(workingWindow == currContext)
					currContext = NULL;
				windows[i].Destroy();
			}
		}
	}
	glfwMakeContextCurrent(currContext);
}

void jlg::WinGroup::Render(const int& ID) {
	if (ID == -1) {
		RenderAll();
	} else if (ID < 0 || ID >= size) {
		std::cerr << "ERROR::WINGROUP::RENDER::Invalid ID" << std::endl;
	} else if (windows[ID].IsActive()) {
		GLFWwindow* currContext = glfwGetCurrentContext();
		windows[ID].Render();
		glfwMakeContextCurrent(currContext);
	} else {
		std::cerr << "ERROR::WINGROUP::RENDER::Window is not active" << std::endl;
	}
}

void jlg::WinGroup::SetCallback(GLFWkeyfun cbfun) {
	for(int i = 0; i < size; i++)
		windows[i].SetCallback(cbfun);
}

void jlg::WinGroup::SetCallback(GLFWwindowclosefun cbfun) {
	for(int i = 0; i < size; i++)
		windows[i].SetCallback(cbfun);
}

jlg::Window& jlg::WinGroup::operator[](int ID) {

	if (ID >= 0 && ID < size) {
		return windows[ID];
	} else {
		std::cerr << "ERROR::WINGROUP::OPERATOR[]::Invalid ID" << std::endl;
		throw std::exception("Invalid accessor");
	}
}