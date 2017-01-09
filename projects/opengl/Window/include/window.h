#pragma once
#include<iostream>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>

namespace jlg {
	enum JLGenum {
		WIN_DEFAULT_WIDTH = 600,
		WIN_DEFAULT_HEIGHT = 400
	};
	struct WindowInfo {
		int width;
		int height;
		const char* title;
		WindowInfo() : width((int)WIN_DEFAULT_WIDTH), height((int)WIN_DEFAULT_HEIGHT), title("window") {}
		WindowInfo(int Width) : width(Width), height((int)WIN_DEFAULT_HEIGHT), title("window") {}
		WindowInfo(int Width, int Height) : width(Width), height(Height), title("window") {}
		WindowInfo(int Width, int Height, const char* Title) : width(Width), height(Height), title(Title) {}
		WindowInfo(const char* Title) : width((int)WIN_DEFAULT_WIDTH), height((int)WIN_DEFAULT_HEIGHT), title(Title) {}
	};

	class Window {
	private:
		bool created;
		static bool isInitialized;
		static void Initialize();
	protected:
		WindowInfo info;
		GLFWwindow* winPtr;
	public:
		Window() : created(false), winPtr(nullptr) {}
		Window(int Width) : created(false), info(Width), winPtr(nullptr) {}
		Window(int Width, int Height) : created(false), info(Width, Height), winPtr(nullptr) {}
		Window(int Width, int Height, const char* Title) : 
			created(false), info(Width, Height, Title), winPtr(nullptr) {}
		Window(const char* Title) : created(false), info(Title), winPtr(nullptr) {}

		inline static bool IsInitialized() { return isInitialized; }

		GLFWwindow* Create(int Width = -1, int Height = -1, const char* Title = nullptr);
		void ForceClose();
		void MakeCurrent();
		void SetViewPort(GLuint x = 0, GLuint y = 0);
		inline GLFWwindow* window() { return winPtr; }
		inline bool IsCreated() const { return created; }
		inline bool ShouldClose() const { return created ? glfwWindowShouldClose(this->winPtr) : false; }
	};
};