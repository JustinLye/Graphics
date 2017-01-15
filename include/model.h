#if !defined(__JLG_MODEL_HEADER__)
#define __JLG_MODEL_HEADER__

#include"texture.h"
#include"shapes.h"

namespace jlg {
	class Model : public Cube {
	public:
		Texture texture;
		Model();
		virtual void BindModel(
			const GLuint& VertexArrayObject,
			const GLuint& VertexBufferObject,
			const GLuint& ElementBufferObject,
			const GLuint& TextureID,
			const GLchar* ImageFilePath);
		virtual void Draw();
	};
};


#endif