#pragma once
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<SOIL2.h>
namespace jlg {
	struct TextureInfo {
		GLenum TextureActivation;
		GLuint TextureID;
		const char* TexturePath;
		unsigned char* TextureImage;
		int Width;
		int Height;
		GLuint ShaderProgramID;
		const char* SamplerName;
		GLint ShaderTextureValue;
	};

	class Texture {
	public:
		TextureInfo info;
		Texture(
			const char* imagePath,
			GLuint shaderProgramID,
			const char* samplerName,
			GLint shaderTextureValue) {
			this->info.TexturePath = imagePath;
			this->info.ShaderProgramID = shaderProgramID;
			this->info.SamplerName = samplerName;
			this->info.ShaderTextureValue = shaderTextureValue;
		}
		void LoadTexture() {
			glGenTextures(1, &this->info.TextureID);
			glBindTexture(GL_TEXTURE_2D, this->info.TextureID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			this->info.TextureImage = SOIL_load_image(
				this->info.TexturePath,
				&this->info.Width,
				&this->info.Height,
				0,
				SOIL_LOAD_RGB);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->info.Width, this->info.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->info.TextureImage);
			glGenerateMipmap(GL_TEXTURE_2D);
			SOIL_free_image_data(this->info.TextureImage);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		void Activate() {
			glActiveTexture(this->info.TextureActivation);
			glBindTexture(GL_TEXTURE_2D, this->info.TextureID);
			glUniform1i(glGetUniformLocation(this->info.ShaderProgramID, this->info.SamplerName), this->info.ShaderTextureValue);
		}

	};
};