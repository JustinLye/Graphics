
#if !defined(__JLG_WINDOW_HEADER__)
#define __JLG_WINDOW_HEADER__
#include<iostream>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>

namespace jlg {
	enum JLGenum {
		WIN_DEFAULT_WIDTH = 600,
		WIN_DEFAULT_HEIGHT = 400,
		WIN_CALLBACK_CURPOS_FUN = 0,
		WIN_CALLBACK_SCROLL_FUN = 1
		//WIN_CALLBACK_INPUT_KEY = 0,
		//WIN_CALLBACK_INPUT_MOUSEMV,
		//WIN_CALLBACK_INPUT_MOUSESR
	};

	struct vec4 {
		GLfloat r;
		GLfloat g;
		GLfloat b;
		GLfloat a;
		vec4() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}
		vec4(
			GLfloat Red,
			GLfloat Green,
			GLfloat Blue,
			GLfloat Alpha) :
			r(Red),
			g(Green),
			b(Blue),
			a(Alpha) {}
	};
	struct WindowInfo {
		int width;
		int height;
		const char* title;
		vec4 clearColor;
		WindowInfo() : width((int)WIN_DEFAULT_WIDTH), height((int)WIN_DEFAULT_HEIGHT), title("window") {}
		WindowInfo(int Width) : width(Width), height((int)WIN_DEFAULT_HEIGHT), title("window") {}
		WindowInfo(int Width, int Height) : width(Width), height(Height), title("window") {}
		WindowInfo(int Width, int Height, const char* Title) : width(Width), height(Height), title(Title) {}
		WindowInfo(const char* Title) : width((int)WIN_DEFAULT_WIDTH), height((int)WIN_DEFAULT_HEIGHT), title(Title) {}
	};

	class Window {
	private:
		bool created;
		bool destroyed;
		static bool isInitialized;
		static void Initialize();
	protected:
		WindowInfo info;
		GLFWwindow* winPtr;
	public:
		
		//constructors
		Window() : created(false), destroyed(false), winPtr(nullptr) {}
		Window(int Width) : created(false), destroyed(false), info(Width), winPtr(nullptr) {}
		Window(int Width, int Height) : created(false), destroyed(false), info(Width, Height), winPtr(nullptr) {}
		Window(int Width, int Height, const char* Title) : 
			created(false), destroyed(false), info(Width, Height, Title), winPtr(nullptr) {}
		Window(const char* Title) : created(false), destroyed(false), info(Title), winPtr(nullptr) {}

		//static member variables
		const static int MAX_WINDOWS;

		//static member functions
		inline static bool IsInitialized() { return isInitialized; }

		//member functions
		GLFWwindow* Create(int Width = -1, int Height = -1, const char* Title = nullptr);
		void Destroy();
		void SetViewPort(GLuint x = 0, GLuint y = 0);
		void MakeCurrent();
		virtual void Render();
		void SetCallback(GLFWkeyfun cbfun);
		void SetCallback(GLFWwindowclosefun cbfun);
		void SetCallback(GLFWcursorposfun cbfun, JLGenum FunType = WIN_CALLBACK_CURPOS_FUN);
		//member variable access
		inline GLFWwindow* window() { return winPtr; }
		inline bool IsCreated() const { return created; }
		inline bool IsDestroyed() const { return destroyed; }
		inline bool IsActive() const { return created && !destroyed; }

		inline void SetClearColor(const vec4& color) {
			info.clearColor = color;
		}
		inline void SetClearColor(GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat Alpha) {
			info.clearColor = vec4(Red, Green, Blue, Alpha);
		}
		inline vec4 GetClearClolor() const { return info.clearColor; }
	
	};

	template<class WindowType = jlg::Window>
	class WinGroup {
	private:
		int size;
		const static char* MAX_WINDOWS_REACHED;
		void AtCapMsg() const;
		GLFWwindow* currContext; //used to restore context.
	protected:
		WindowType* windows;
		void InsertNewWindow(int Width = -1, int Height = -1, const char* Title = nullptr);
		void RenderAll();
	public:
		//constructors
		WinGroup();

		//destructor
		~WinGroup();

		//static member variables
		const static int MAX_WINDOWS;
		
		//member functions
		void PushBack();
		void PushBack(int Width);
		void PushBack(int Width, int Height);
		void PushBack(int Width, int Height, const char* Title);
		void PushBack(const char* Title);
		void Render(const int& ID = -1);
		void SetCallback(GLFWkeyfun cbfun);
		void SetCallback(GLFWwindowclosefun cbfun);
		//member query functions
		inline bool AtCapacity() const { return size == MAX_WINDOWS; }
		inline bool IsActive() const {
			for (int i = 0; i < size; i++)
				if(windows[i].IsActive())
					return true;
			return false;
		}

		//operators
		WindowType& operator[](int ID);
	};

};
#endif

#if !defined(__JLG_WINDOW_CPP__)
#include"..\src\window.cpp"
#endif
