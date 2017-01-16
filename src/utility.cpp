#include"utility.h"

//No allocation. Initialize count and dims to zero
jlg::VertexData::VertexData() :
	vertices(nullptr),
	count(0),
	dims(0),
	length(0),
	size(0) {}

//If Vertices is not null, memory will be allocated per count and dim. Copy info pointed to by Vertices
jlg::VertexData::VertexData(
	const GLuint& Count,
	const GLuint& Dimensions,
	const GLfloat* Vertices) :
	vertices(nullptr),
	count(Count),
	dims(Dimensions),
	length(Count * Dimensions),
	size((Count * Dimensions) * sizeof(GLfloat)) {
	vertices = new GLfloat[length];
	if (Vertices != nullptr) {
		for (GLuint i = 0; i < length; i++)
			vertices[i] = Vertices[i];
	}
}

//Copy constructor allocates vertices and copies info
jlg::VertexData::VertexData(const VertexData& CopyShape) :
	vertices(nullptr),
	count(CopyShape.count),
	dims(CopyShape.dims),
	length(CopyShape.count * CopyShape.dims),
	size((CopyShape.count * CopyShape.dims) * sizeof(GLfloat)) {
	if (length > 0) {
		vertices = new GLfloat[length];
		if (CopyShape.vertices != nullptr)
			for (GLuint i = 0; i < length; i++)
				vertices[i] = CopyShape.vertices[i];
	}
}

//Allocates vertices, moves all members, then sets count and dims to zero and deletes vertices of MoveShape and sets vertices pointer to null
jlg::VertexData::VertexData(VertexData&& MoveShape) :
	vertices(nullptr),
	count(std::move(MoveShape.count)),
	dims(std::move(MoveShape.dims)),
	length(std::move(MoveShape.length)),
	size(std::move(MoveShape.size)) {
	assert(count * dims == length && length * sizeof(GLfloat) == size);
	if (length > 0) {
		vertices = new GLfloat[length];
		if (MoveShape.vertices != nullptr) {
			for (GLuint i = 0; i < length; i++) {
				vertices[i] = std::move(MoveShape.vertices[i]);
			}
			GLfloat* delPtr = MoveShape.vertices;
			MoveShape.vertices = nullptr;
			delete[] delPtr;
		}
	}
	MoveShape.vertices = nullptr;
	MoveShape.count = 0;
	MoveShape.dims = 0;
	MoveShape.length = 0;
	MoveShape.size = 0;
}

//Ensures resources are released
jlg::VertexData::~VertexData() {
	if (vertices != nullptr) {
		GLfloat* delPtr = vertices;
		vertices = nullptr;
		delete[] delPtr;
	}
}

//initializes all members to zero.
jlg::Attrib::Attrib() :
	index(0),
	count(0),
	stride(0),
	offset(0) {}

//initialize members per arguments
jlg::Attrib::Attrib(
	const GLuint& Index,
	const GLuint& Count,
	const GLuint& Stride,
	const GLuint& Offset) :
	index(Index),
	count(Count),
	stride(Stride),
	offset(Offset) {}

//Trivial copy constructor
jlg::Attrib::Attrib(const Attrib& CopyAttrib) :
	index(CopyAttrib.index),
	count(CopyAttrib.count),
	stride(CopyAttrib.stride),
	offset(CopyAttrib.offset) {}

//Moves members and resets MoveAttrib members to zero.
jlg::Attrib::Attrib(Attrib&& MoveAttrib) :
	index(std::move(MoveAttrib.index)),
	count(std::move(MoveAttrib.count)),
	stride(std::move(MoveAttrib.stride)),
	offset(std::move(MoveAttrib.offset)) {
	MoveAttrib.index = 0;
	MoveAttrib.count = 0;
	MoveAttrib.stride = 0;
	MoveAttrib.offset = 0;
}

//trivial assignment operator
jlg::Attrib& jlg::Attrib::operator=(const Attrib& CopyAttrib) {
	index = CopyAttrib.index;
	count = CopyAttrib.count;
	stride = CopyAttrib.stride;
	offset = CopyAttrib.offset;
	return *this;
}

const GLfloat jlg::primative_shapes::VERT_DATA_CUBE_VERTICES[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

const GLuint jlg::primative_shapes::VERT_DATA_CUBE_COUNT = 36;
const GLuint jlg::primative_shapes::VERT_DATA_CUBE_DIMS = 5;
const jlg::VertexData VERTEX_DATA_CUBE(jlg::primative_shapes::VERT_DATA_CUBE_COUNT, jlg::primative_shapes::VERT_DATA_CUBE_DIMS, jlg::primative_shapes::VERT_DATA_CUBE_VERTICES);
const jlg::Attrib ATTRIB_CUBE_POSITION_COORD(0, 3, 5, 0);
const jlg::Attrib ATTRIB_CUBE_TEXTURE_COORD(1, 2, 5, 3);