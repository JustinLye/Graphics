#pragma once
#include<iostream>
#include<assert.h>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"SOIL2\SOIL2.h"

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

	//Container used to store Attrib structures.
	//Designed for use as member of Shape class.
	class ShapeAttribs {
	private:
		//Internal properties
		GLuint length; //Total number of Attrib structs in container
		GLuint capacity; //Total available space
		GLuint capacityOnReserve; //Minimum capacity. Capacity will not drop below this limit.
		Attrib* attribs; //Array of Attrib structs
		//Internal methods
		bool Resize(const GLuint& NewCapacity = 0); //Internal member function used to reallocate space when needed
		bool DownSize() const; //Internal method to test if the attribs array should be down sized. This method is called by the PopBack method.
		bool InsertAttrib(const GLuint& Index, const GLuint& Count, const GLuint& Stride, const GLuint& Offset); //Creates new Attrib struct and appends it to the end of attribs array. If AtMaxCapacity is true then no action is taken.
		void SetAndValidateReserveCapacity(const GLuint& ReserveCapacity); //Internal method used to update capacityOnReserve. This method should be used to update capacityOnReserve opposed to direct assignment. This method will also allocate space if needed.
		bool IsOkayToCopyOrMove(const ShapeAttribs& AttribsObj) const; //Internal method used to validate a ShapeAttribs object before copy, move, or assignment
		bool Copy(const ShapeAttribs& AttribsObj);  //Internal method used copy a ShapeAttribs object. Calls IsOkayToCopyOrMove. Returns false if copy did not occur due to invalid data.
	public:
		//Static public read-only members
		static const GLuint SHAPE_ATTRIBS_MAX_CAPACITY; //Maximum number of attribs allowed in ShapeAttribs container
		static const GLuint SHAPE_ATTRIBS_INITIAL_CAPACITY; //Default ShapeAttribs capacity.
		static const GLfloat SHAPE_ATTRIBS_MIN_SPARSITY_RATIO; //If length / capacity is less than this ratio, then attribs can be considered for a downsize. Downsize event also depends on the value of capacity - length.
		static const GLuint SHAPE_ATTRIBS_MAX_FREE_SPACE; //If capacity - length is greater than this value, then attribs can be considered for a downsize. Downsize event also depends on the sparsity ratio.

		//Constructors
		ShapeAttribs(); //Initialize all to zero. Does not perform memory allocation.
		ShapeAttribs(const GLuint& ReserveCapacity); //Allocates space per ReserveCapacity arg. Initializes capacity to ReserveCapacity.
		ShapeAttribs(const ShapeAttribs& CopyAttribs); //Allocates space and copies Attrib structs from CopyAttribs. No allocation is performed if CopyAttribs is empty.
		ShapeAttribs(ShapeAttribs&& MoveAttribs); //Allocates space and moves Attrib structs from MoveAttribs. If Move attribs is empty no allocation is performed. Releases MoveAttribs attribs array, sets pointer to nullptr and sets capacity and length to zero.
		
		//Destructor
		~ShapeAttribs(); //Ensures resources are released.

		//Public member methods
		void PushBack(const GLuint& Index, const GLuint& Count, const GLuint& Stride, const GLuint& Offset); //Calls InsertAttrib, which creates new Attrib struct and appends it to the end of attribs array.
		void PushBack(const Attrib& AttribObj); //Calls InsertAttrib, which creates new Attrib struct and appends it to the end of attribs array.
		void PopBack(); //Removes last attrib struct in attribs array. Reallocates if sparsity criteria met (i.e. DownSize() is equal to true).
		void Reserve(const GLuint& ReserveCapacity); //Sets minimum available free space. Immediately allocates space if capacity is below ReserveCapacity at time of function call. No modifications to the attribs array or capacity will be made if ReserveCapacity is less than current capacity. However, capacity will not drop below the reserve capacity.
		void Clear(); //Releases allocated memory, sets length and capacity to zero and attribs is set to nullptr.

		//Public accessors to internal properties
		inline GLuint Length() const { return length; }
		inline GLuint Capacity() const { return capacity; }
		inline GLuint CapacityOnReserve() const { return capacityOnReserve; }
		inline bool IsEmpty() const { return (length == 0); }
		inline GLuint AvailableSpace() const { return (capacity - length); }
		inline bool AtMaxCapacity() const { return length >= SHAPE_ATTRIBS_MAX_CAPACITY; }
		//Public operators
		const Attrib& operator[](const GLuint& Index); //Random access to attribs array. **NOTICE** operator will NOT BOUNDS CHECK. Bounds checking is the responsibility of the user.
	}

	class Shape {
	protected:
		VertexData data;
	public:
		Shape();

	};

	class Cube : public Shape {
	protected:
		void AllocateVertexData();
		GLfloat* points;
	public:
		Cube();
		virtual void BindBuffer(const GLuint& VertexArrayObject, const GLuint& VertexBufferObject);
		virtual void Draw();
	};



};

