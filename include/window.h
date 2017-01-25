
#if !defined(__JLG_WINDOW_HEADER__)
#define __JLG_WINDOW_HEADER__
#include<iostream>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"utility.h"

namespace jlg {
	
	class Window;
	class CallbackWrapper {
	private:
		CallbackWrapper() {}
		CallbackWrapper(const CallbackWrapper&) {}
		CallbackWrapper(CallbackWrapper&&) {}
		static Window* windowPtr;
		inline static void SetCurrentWindow(Window* SetWindow) { windowPtr = SetWindow; }
	protected:
		static void KeyPressEvent(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void MouseMoveEvent(GLFWwindow* window, double xpos, double ypos);
		static void MouseScrollEvent(GLFWwindow* window, double xoffset, double yoffset);
		static void DoMovement();

	public:
		static void BindCallbackEvents(Window* window);
		static void HandleCallbackEvents(Window* window);
	};



	class Window : public WindowSpecs {
	protected:
		bool created;
		bool destroyed;
		static bool initialized;
		static void Initialize();
	public:
		GLFWwindow* window;
		
		void Create();
		void Destroy();
		void SetCallback(GLFWkeyfun cbfun);
		void SetCallback(GLFWwindowclosefun cbfun);
		void SetCallback(GLFWcursorposfun cbfun, JLGenum FunType);

		inline void SetKey(int KeyIndex, bool KeyValue) { keys[KeyIndex] = KeyValue; }

		inline void ClearColor(const Color& WinColor) { color = WinColor; }
		inline void Width(const GLuint& WinWidth) { width = WinWidth; }
		inline void Height(const GLuint& WinHeight) { height = WinHeight; }
		inline void Title(const GLchar* WinTitle) { title = WinTitle; }
		

		inline bool IsActive() const { return created && !destroyed; }
		inline static bool IsInitialized() { return initialized; }

	};


};
#endif
