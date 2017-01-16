#if !defined(__JLG_SCENE_HEADER__)
#define
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"model.h"
#include"Shader.h"
#include"texture.h"
#include"camera.h"


namespace jlg {
	struct SceneSpecs {
		const GLchar* vertexShaderPath;
		const GLchar* fragmentShaderPath;
		const GLchar* imageFilePath;
		const GLchar* modelUniformName;
		const GLchar* viewUniformName;
		const GLchar* projUniformName;
		const GLchar* textureUniformName;
		GLuint VAO;
		GLuint VBO;
		GLuint TexID;
	};

	class Scene {
	public:
		SceneSpecs specs;
		Shader shader;
		Camera camera;
		Texture texture;
		Model model;
		glm::mat4 view;
		glm::mat4 projection;

	};
};

#endif