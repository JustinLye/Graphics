#if !defined(__JLG_VIEW_MANAGER_HEADER__)
#define __JLG_VIEW_MANAGER_HEADER__

#include"camera.h"
#include"Shader.h"
#include"texture.h"
#include"shapes.h"

namespace jlg {
	struct ViewNames {
		const char* VertexShaderPath;
		const char* FragmentShaderPath;
		const char* TextureImagePath;
		const char* ModelUniformName;
		const char* ViewUniformName;
		const char* ProjUniformName;
		const char* TextureUniformName;
		ViewNames(
			const char* viVertexShaderPath,
			const char* viFragmentShaderPath,
			const char* viTextureImagePath,
			const char* viModelUniformName,
			const char* viViewUniformName,
			const char* viProjUniformName,
			const char* viTextureUniformName) :
			VertexShaderPath(viVertexShaderPath),
			FragmentShaderPath(viFragmentShaderPath),
			TextureImagePath(viTextureImagePath),
			ModelUniformName(viModelUniformName),
			ViewUniformName(viViewUniformName),
			ProjUniformName(viProjUniformName),
			TextureUniformName(viTextureUniformName) {}
		ViewNames() :
			VertexShaderPath(nullptr),
			FragmentShaderPath(nullptr),
			TextureImagePath(nullptr),
			ModelUniformName(nullptr),
			ViewUniformName(nullptr),
			ProjUniformName(nullptr),
			TextureUniformName(nullptr) {}
		inline bool IsComplete() const {
			return(
				VertexShaderPath != nullptr &&
				FragmentShaderPath != nullptr &&
				TextureImagePath != nullptr &&
				ModelUniformName != nullptr &&
				ViewUniformName != nullptr &&
				ProjUniformName != nullptr &&
				TextureUniformName != nullptr);
		}
	};
	struct ViewBufferIDs {
		GLuint VAO;
		GLuint VBO;
		GLuint TexID;
	};
	struct ViewData {
		ViewNames names;
		ViewBufferIDs IDs;
		GLfloat screenWidth;
		GLfloat screenHeight;
		GLfloat clipNear;
		GLfloat clipFar;
		inline GLfloat AspectRatio() const { return screenWidth / screenHeight; }
		bool keys[1024];
		ViewData() : 
			screenWidth(800.0f),
			screenHeight(600.0f),
			clipNear(0.01f),
			clipFar(1000.0f) {
			for(int i = 0; i < 1024; i++)
				keys[i] = false;
		}
	};
	class ViewManager {
	protected:
		
		void GenerateBuffers();
		void BindData();
		inline void BindTexture() {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, data.IDs.TexID);
			glUniform1i(glGetUniformLocation(shader.Program, data.names.TextureUniformName),0);
		}
		inline void BindMVPMatricesAndDraw() {
			view = camera.GetViewMatrix();
			projection = glm::perspective(camera.Zoom, data.AspectRatio(), data.clipNear, data.clipFar);
			shader.LoadUniformMatrix4fv(data.names.ViewUniformName, view);
			shader.LoadUniformMatrix4fv(data.names.ProjUniformName, projection);
			glm::mat4 temp;
			model = glm::translate(temp, glm::vec3(0.0f, 0.0f, 0.0f));
			model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.3f, 0.5f));
			glBindVertexArray(data.IDs.VAO);
			shader.LoadUniformMatrix4fv(data.names.ModelUniformName, model);
			cube.Draw();
			glBindVertexArray(0);
		}
	public:
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		Shader shader;
		Texture texture;
		Cube cube;
		Camera camera;
		ViewData data;
		ViewManager();
		ViewManager(const ViewNames& Names);
		void Initialize();
		inline void SetViewNames(const ViewNames& Names) { data.names = Names; }
		inline void UpdateView() {
			shader.UseProgram();
			BindTexture();
			BindMVPMatricesAndDraw();
		}
	};
};

#endif