#if !defined(__JLG_WINDOW3D_HEADER__)
#define __JLG_WINDOW3D_HEADER__
#include"window.h"
#include"Shader.h"

namespace jlg {
	class Window3d : public jlg::Window {
	protected:
		jlg::Shader shader;
	public:
		Window3d() : Window() {}
		Window3d(int Width, const char* vertexShaderPath = nullptr, const char* fragmentShaderPath = nullptr) :
			Window(Width) {
			if(vertexShaderPath != nullptr && fragmentShaderPath != nullptr)
				LoadShader(vertexShaderPath, fragmentShaderPath);
		}
		Window3d(
			int Width,
			int Height,
			const char* vertexShaderPath = nullptr,
			const char* fragmentShaderPath = nullptr) :
			Window(Width, Height) {
			if (vertexShaderPath != nullptr && fragmentShaderPath != nullptr)
				LoadShader(vertexShaderPath, fragmentShaderPath);
		}
		Window3d(
			int Width,
			int Height,
			const char* Title,
			const char* vertexShaderPath = nullptr,
			const char* fragmentShaderPath = nullptr) :
			Window(Width, Height, Title) {
			if (vertexShaderPath != nullptr && fragmentShaderPath != nullptr)
				LoadShader(vertexShaderPath, fragmentShaderPath);
		}
		Window3d(
			const char* Title,
			const char* vertexShaderPath = nullptr,
			const char* fragmentShaderPath = nullptr) :
			Window(Title) {
			if (vertexShaderPath != nullptr && fragmentShaderPath != nullptr)
				LoadShader(vertexShaderPath, fragmentShaderPath);
		}
		Window3d(const char* vertexShaderPath, const char* fragmentShaderPath) : Window() {
			LoadShader(vertexShaderPath, fragmentShaderPath);
		}
		virtual void Render();
		void LoadShader(const char* vertexShaderPath, const char* fragmentShaderPath);
	};
};

#endif