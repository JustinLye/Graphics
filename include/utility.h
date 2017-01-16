#if !defined(__JLG_UTILITY_HEADER__)
#define __JLG_UTILITY_HEADER__
#include<iostream>
#include<assert.h>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>

namespace jlg {


	//Structure to store basic vertex information.
	//Intended to be used as a member of the Shape class.
	//**NOTICE**Member length is NOT managed by ShapeData.
	//This applies to the size member since size == length * sizeof(GLfloat)
	//It is the responsibilty of the user to ensure (count * dims == length) and (length * sizeof(GLfloat) == size).
	//ShapeData will set the length and size members ONLY ONCE at construction.
	//If count and dims are know at construction length will be set to count * dims and size will be set to length * sizeof(GLfloat).
	//Otherwise length and size are initialized to 0.
	struct VertexData {
		GLfloat* vertices; //shape vertex information
		GLuint count; //number of vertices (rows)
		GLuint dims; //dimensions of vertex data (cols)
		GLuint length; //total elements in vertex data array (row * cols)
		GLsizeiptr size; //length * sizeof(GLfloat)
		VertexData(); //No allocation. Initialize count and dims to zero
		VertexData(const GLuint& Count, const GLuint& Dimensions, const GLfloat* Vertices = nullptr); //If Vertices is not null, memory will be allocated per count and dim. Copy info pointed to by Vertices
		VertexData(const VertexData& CopyShape); //Copy constructor allocates vertices and copies info
		VertexData(VertexData&& MoveShape); //Allocates vertices, moves all members, then sets count and dims to zero and deletes vertices of MoveShape and sets vertices pointer to null
		~VertexData(); //Ensures resources are released
	};

	//Structure to store vertex array attribute info.
	//Intended for use with ShapeAttribs
	struct Attrib {
		GLuint index; //index of attribute.
		GLuint count; //count of vertices in subset to apply attribute to.
		GLuint stride; //vertices between next vertices subset
		GLuint offset; //offset to the beginning of subset
		Attrib(); //initializes all members to zero.
		Attrib(const GLuint& Index, const GLuint& Count, const GLuint& Stride, const GLuint& Offset); //initialize members per arguments
		Attrib(const Attrib& CopyAttrib); //Trivial copy constructor
		Attrib(Attrib&& MoveAttrib); //Moves members and resets MoveAttrib members to zero.
									 //Operators
		Attrib& operator=(const Attrib& CopyAttrib); //assignment operator.

	};

	namespace primative_shapes {
		extern const GLfloat VERT_DATA_CUBE_VERTICES[];
		extern const GLuint VERT_DATA_CUBE_COUNT;
		extern const GLuint VERT_DATA_CUBE_DIMS;
		extern const VertexData VERTEX_DATA_CUBE;
		extern const Attrib ATTRIB_CUBE_POSITION_COORD;
		extern const Attrib ATTRIB_CUBE_TEXTURE_COORD;
	};

	struct ShaderData {
		const GLchar* vertexShaderPath;
		const GLchar* fragmentShaderPath;
		const GLchar* imageFilePath;
		const GLchar* modelUniformName;
		const GLchar* viewUniformName;
		const GLchar* projUniformName;
		const GLchar* textureUniformName;
		GLuint textureID;
		
	};

};

#endif