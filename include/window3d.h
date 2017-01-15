#if !defined(__JLG_WINDOW3D_HEADER__)
#define __JLG_WINDOW3D_HEADER__
#include"window.h"
#include"ViewManager.h"
namespace jlg {
	class Window3d;
	class CallBackWrapper {
	private:
		CallBackWrapper() {}
		CallBackWrapper(const CallBackWrapper&) {}
		CallBackWrapper(CallBackWrapper&&) {}
		static Window3d* winView;
		inline static void SetCurrentWindow(Window3d* window) { winView = window; }
	protected:
		static void KeyPressEvent(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void MouseMoveEvent(GLFWwindow* window, double xpos, double ypos);
		static void MouseScrollEvent(GLFWwindow* window, double xoffset, double yoffset);
		static void DoMovement();
	public:
		static void BindCallBackEvents(Window3d* window);
		static void HandleCallBackEvents(Window3d* window, bool ManageContext = false);
	};
	class Window3d : public jlg::Window {
	private:		
	protected:
		
		void SetCallbacks();
	public:
		bool firstMouse;
		GLfloat deltaTime;
		GLfloat lastFrame;
		GLfloat lastX;
		GLfloat lastY;
		jlg::ViewManager viewManager;
		Window3d() : 
			Window(),
			deltaTime(0.0f),
			lastFrame(0.0f),
			lastX(400.0f),
			lastY(300.0f),
			firstMouse(false) {
		}
		Window3d(int Width, const char* vertexShaderPath = nullptr, const char* fragmentShaderPath = nullptr) :
			Window(Width),
			deltaTime(0.0f),
			lastFrame(0.0f),
			lastX(400.0f),
			lastY(300.0f),
			firstMouse(false) {
			//if(vertexShaderPath != nullptr && fragmentShaderPath != nullptr)
			//	LoadShader(vertexShaderPath, fragmentShaderPath);
		}
		Window3d(
			int Width,
			int Height,
			const char* vertexShaderPath = nullptr,
			const char* fragmentShaderPath = nullptr) :
			Window(Width, Height),
			deltaTime(0.0f),
			lastFrame(0.0f),
			lastX(400.0f),
			lastY(300.0f),
			firstMouse(false) {
			//if (vertexShaderPath != nullptr && fragmentShaderPath != nullptr)
			//	LoadShader(vertexShaderPath, fragmentShaderPath);
		}
		Window3d(
			int Width,
			int Height,
			const char* Title,
			const char* vertexShaderPath = nullptr,
			const char* fragmentShaderPath = nullptr) :
			Window(Width, Height, Title),
			deltaTime(0.0f), 
			lastFrame(0.0f),
			lastX(400.0f),
			lastY(300.0f),
			firstMouse(true) {
			//if (vertexShaderPath != nullptr && fragmentShaderPath != nullptr)
			//	LoadShader(vertexShaderPath, fragmentShaderPath);
		}
		Window3d(
			const char* Title) :
			Window(Title),
			deltaTime(0.0f),
			lastFrame(0.0f),
			lastX(400.0f),
			lastY(300.0f),
			firstMouse(true) {
			//if (vertexShaderPath != nullptr && fragmentShaderPath != nullptr)
			//	LoadShader(vertexShaderPath, fragmentShaderPath);
			std::cout << "Window3d constructor" << std::endl;
		}
		//Window3d(const char* vertexShaderPath, const char* fragmentShaderPath) : Window() {
		//	LoadShader(vertexShaderPath, fragmentShaderPath);
		//}
		virtual void Render(GLfloat DeltaTime);
		//void LoadShader(const char* vertexShaderPath, const char* fragmentShaderPath);
		//void LoadVertexArrayObject(const char* imagePath);
		void Initialize();
		//inline void ScaleCube(const GLfloat& Multiplier) { vao.cube.Scale(Multiplier); }

	};
};

#endif