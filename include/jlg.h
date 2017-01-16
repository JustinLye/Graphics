#if !defined(__JLG_HEADER__)
#define __JLG_HEADER__
#include"utility.h"
#include"Shader.h"
#include"texture.h"
#include"model.h"
#include"camera.h"
#include"shapes.h"

namespace jlg {
	class ShaderManager : Shader {
	public:
		const GLchar* textureName;
		const GLchar* modelName;
		const GLchar* viewName;
		const GLchar*
		GLuint textureID;
		Texture texture;
	};
};

#endif