#if !defined(__JLG_SHAPES_HEADER__)
#define __JLG_SHAPES_HEADER__
#include<iostream>
#include<assert.h>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"utility.h"


namespace jlg {

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
		
		//Calls InsertAttrib, which creates new Attrib struct and appends it to the end of attribs array.
		inline void PushBack(const GLuint& Index, const GLuint& Count, const GLuint& Stride, const GLuint& Offset) {
			InsertAttrib(Index, Count, Stride, Offset);
		}

		//Calls InsertAttrib, which creates new Attrib struct and appends it to the end of attribs array.
		inline void PushBack(const Attrib& AttribObj) {
			InsertAttrib(AttribObj.index, AttribObj.count, AttribObj.stride, AttribObj.offset);
		}
		//Removes last attrib struct in attribs array.
		//Reallocates if sparsity criteria met (i.e. DownSize() is equal to true).
		inline void ShapeAttribs::PopBack() {
			if (length <= 0) {
				std::cerr << "WARNING::SHAPE_ATTRIBS::POP_BACK::Attempt to pop back empty list" << std::endl;
				if (DownSize()) {
					Resize(SHAPE_ATTRIBS_INITIAL_CAPACITY);
				}
				return;
			}
			length--;
			if (DownSize()) {
				Resize(floorf(((GLfloat)(capacity - length)) / 2.0f) + length);
			}
		}
		//Sets minimum capacity.
		//Immediately allocates space if capacity is below ReserveCapacity at time of function call.
		//No modifications to the attribs array or capacity will be made if ReserveCapacity is less than current capacity.
		//However, capacity will not drop below the reserve capacity.
		inline void Reserve(const GLuint& ReserveCapacity) {
			SetAndValidateReserveCapacity(ReserveCapacity);
		}

		//Releases allocated memory, sets length and capacity to zero and attribs is set to nullptr.
		inline void Clear() {
			length = 0;
			capacity = 0;
			capacityOnReserve = 0;
			if (attribs != nullptr) {
				Attrib* delPtr = attribs;
				attribs = nullptr;
				delete[] delPtr;
			}
		}

		//Public accessors to internal properties

		inline const GLuint& Length() const { return length; }
		inline const GLuint& Capacity() const { return capacity; }
		inline const GLuint& CapacityOnReserve() const { return capacityOnReserve; }
		inline bool IsEmpty() const { return (length == 0); }
		inline const GLuint& AvailableSpace() const { return (capacity - length); }
		inline bool AtMaxCapacity() const { return length >= SHAPE_ATTRIBS_MAX_CAPACITY; }

		//Public operators

		//Random access to attribs array. **NOTICE** operator will NOT BOUNDS CHECK. Bounds checking is the responsibility of the user.
		inline const Attrib& operator[](const GLuint& Index) {
			return attribs[Index];
		}
	};


	struct ShapeData {
		VertexData vertexData;
		ShapeAttribs attributes;
		ShapeData() {}
		ShapeData(const ShapeData& CopyShapeData) :
			vertexData(CopyShapeData.vertexData),
			attributes(CopyShapeData.attributes) {}
		ShapeData(ShapeData&& MoveShapeData) :
			vertexData(std::move(MoveShapeData.vertexData)),
			attributes(std::move(MoveShapeData.attributes)) {}
		ShapeData(const VertexData& Data) : vertexData(Data) {}
		ShapeData(const ShapeAttribs& Attributes) : attributes(Attributes) {}
		ShapeData(const VertexData& Data, const ShapeAttribs& Attributes) :
			vertexData(Data),
			attributes(Attributes) {}
	};

	class Shape {
	protected:
		//Internal Properties
		//Vertex and Vertex attribute information
		ShapeData data;

		//Internal Methods
		void ClearVertexData(); //Releases any memory allocated to data.vertexData and resets members to zero or nullptr
		void ResetVertexData(const GLfloat* VertexArray, const GLuint& Count, const GLuint& Dimensions); //Clears vertexData struct (call to ClearVertexData) then sets vertexData struct members per arguments.
		void BufferVertexAttributes();
		inline void BufferVertexData() {
			glBufferData(GL_ARRAY_BUFFER, data.vertexData.size, data.vertexData.vertices, GL_STATIC_DRAW);
			BufferVertexAttributes();
		}
	public:
		//Constructors

		Shape();
		Shape(const Shape& CopyShape);
		Shape(Shape&& MoveShape);
		Shape(const ShapeData& InitShapeData);
		Shape(const VertexData& InitVertexData);
		Shape(const ShapeAttribs& InitShapeAttribs);
		Shape(const VertexData& InitVertexData, const ShapeAttribs& InitShapeAttribs);

		//Public Member Methods

		//Released memory used by data.vertexData if needed.
		//Allocated memory to data.vertexData.
		//Copies VertexArray into data.vertexData.
		inline void SetVertexData(const GLfloat* VertexArray, const GLuint& Count, const GLuint& Dimensions) {
			ResetVertexData(VertexArray, Count, Dimensions);
		}

		//Binds and Buffers data
		inline virtual void Buffer(const GLuint& VertexArrayObject, const GLuint& VertexBufferObject) {
			glBindVertexArray(VertexArrayObject);
			glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
			BufferVertexData();
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		virtual void Draw() {
			glDrawArrays(GL_ARRAY_BUFFER, 0, data.vertexData.count);
		}

		//Internal Property Accessors

		//Vertex Array Data Properties

		inline const GLuint& VertexCount() const { return data.vertexData.count; }
		inline const GLuint& VertexDimensions() const { return data.vertexData.dims; }
		inline const GLuint& VertexLength() const { return data.vertexData.length; }
		inline const GLsizeiptr& VertexSize() const { return data.vertexData.size; }
		inline const GLfloat* Vertices() const { return data.vertexData.vertices; }

		//Attributes Container Functions

		inline void PushAttribute(const GLuint& Index, const GLuint& Count, const GLuint& Stride, const GLuint& Offset) {
			data.attributes.PushBack(Index, Count, Stride, Offset);
		}
		inline void PushAttribute(const Attrib& AttribObj) {
			data.attributes.PushBack(AttribObj);
		}
		inline void PopAttribute() {
			data.attributes.PopBack();
		}
		inline void ReserveAttibCapacity(const GLuint& ReserveCapacity) {
			data.attributes.Reserve(ReserveCapacity);
		}
		inline void ClearAttributes() {
			data.attributes.Clear();
		}
		inline const GLuint& AttributeCount() const {
			return data.attributes.Length();
		}
		inline const GLuint& AttributeCapacity() const {
			return data.attributes.Capacity();
		}
		inline const GLuint& AttribCapacityOnReserve() const {
			return data.attributes.CapacityOnReserve();
		}
		inline bool NoAttributes() const {
			return data.attributes.IsEmpty();
		}
		inline const GLuint& AttribAvailableSpace() const {
			return data.attributes.AvailableSpace();
		}
		inline bool AttribAtMaxCapacity() const {
			return data.attributes.AtMaxCapacity();
		}

		inline const Attrib& Attribute(const GLuint& Index) {
			return data.attributes[Index];
		}
	};

	class Cube : public Shape {
	public:
		Cube() : Shape() {
			ResetVertexData(jlg::primative_shapes::VERT_DATA_CUBE_VERTICES, jlg::primative_shapes::VERT_DATA_CUBE_COUNT, jlg::primative_shapes::VERT_DATA_CUBE_DIMS);
			data.attributes.PushBack(jlg::primative_shapes::ATTRIB_CUBE_POSITION_COORD);
			data.attributes.PushBack(jlg::primative_shapes::ATTRIB_CUBE_TEXTURE_COORD);
		}
		inline void Draw() {
			glDrawArrays(GL_VERTEX_ARRAY, 0, data.vertexData.count);
		}
	};

};

#endif

