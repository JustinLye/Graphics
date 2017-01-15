#if !defined(__JLG_TEXTURE_HEADER__)
#define __JLG_TEXTURE_HEADER__
#include<iostream>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<SOIL2/SOIL2.h>

namespace jlg {
	class Texture {
	public:
		const GLuint* texID;
		const char* imagePath;
		const char* uniformName;
		Texture();
		Texture(const char* ImageFilePath, const char* UniformName);
		
		inline bool IsInitialized() const { return (imagePath != nullptr && uniformName != nullptr); }
		void BufferTexture(const GLuint& TextureID);
	};
};

#endif