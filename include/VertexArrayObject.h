#if !defined(__JLG_VERTEX_ARRAY_OBJECT_HEADER__)
#define __JLG_VERTEX_ARRAY_OBJECT_HEADER__
#include<iostream>
#include"shapes.h"

namespace jlg {
	class VertexArrayObject {
	private:
		bool initialized;
	public:
		VertexArrayObject() : initialized(false) {}
		VertexArrayObject(const char* imagePath);
		~VertexArrayObject() {
			std::cout << "vertex array destructor" << std::endl;
			if (initialized) {
				glDeleteVertexArrays(1, &VAO);
				glDeleteBuffers(1, &VBO);
				glDeleteTextures(1, &texID);
			}
			std::cout << "finished vertex array destructor" << std::endl;
		}
		
		Cube cube;
		GLuint VBO;
		GLuint VAO;
		GLuint texID;
		void InitializeObject(const char* imagePath);
		void LoadTexture(const char* imagePath);
		void LoadShape();

	};
};

#endif