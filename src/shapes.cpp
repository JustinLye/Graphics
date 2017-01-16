#include"..\include\shapes.h"

const GLuint jlg::ShapeAttribs::SHAPE_ATTRIBS_MAX_CAPACITY = 64;
const GLuint jlg::ShapeAttribs::SHAPE_ATTRIBS_INITIAL_CAPACITY = 4;
const GLfloat jlg::ShapeAttribs::SHAPE_ATTRIBS_MIN_SPARSITY_RATIO = 0.2f;
const GLuint jlg::ShapeAttribs::SHAPE_ATTRIBS_MAX_FREE_SPACE = 32;

//Internal member function used to reallocate space when needed.
//Returns true if resize was successful.
//Returns false if NewCapacity argument is zero and Max Capacity has already been reached.
//**CAUTION** It is best to check capacity limits before calling Resize();
bool jlg::ShapeAttribs::Resize(const GLuint& NewCapacity) {
	bool canResize = !AtMaxCapacity();
	if (!canResize) {
		std::cerr << "WARNING::SHAPE ATTRIBS::RESIZE::No action taken. Capacity limit has already be reached." << std::endl;
		return false;
	}

	//determine the appropriate capacity
	if (NewCapacity <= 0) {
		if(capacity <= 0)
			capacity = SHAPE_ATTRIBS_INITIAL_CAPACITY;
		else
			capacity *= 2;
	} else if (NewCapacity > 0 && NewCapacity <= SHAPE_ATTRIBS_MAX_CAPACITY) {
		capacity = NewCapacity;
	} else if (NewCapacity > SHAPE_ATTRIBS_MAX_CAPACITY) {
		std::cerr << "WARNING::SHAPE ATTRIBS::RESIZE::New Capacity exceeds Max Capacity of ShapeAttribs. Capacity was set to SHAPE_ATTRIBS_MAX_CAPACITY" << std::endl;
		capacity = SHAPE_ATTRIBS_MAX_CAPACITY;
	} else if (NewCapacity < 0) {
		//I do not believe this check is necessary because NewCapacity is unsigned (i.e. GLuint). Also, the test will never actually be performed since NewCapacity will never be < 0.
		//I'm adding the test any way because it makes me feel more comfortable.
		std::cerr << "WARNING::SHAPE ATTRIBS::RESIZE::New Capacity cannot be less than zero. Capacity was set to SHAPE_ATTRIBS_INITIAL_CAPACITY" << std::endl;
		capacity = SHAPE_ATTRIBS_INITIAL_CAPACITY;
	}

	//make sure capacity is not over max capacity limit
	if(capacity > SHAPE_ATTRIBS_MAX_CAPACITY)
		capacity = SHAPE_ATTRIBS_MAX_CAPACITY;

	//override for reserve capacity
	//**NOTE** capacityOnReserve is validated against size limits when it is set. Therefore it is safe to assign capacity to 
	//         capacityOnReserve with out testing 0 <= capacityOnReserve <= SHAPE_ATTRIBS_INITIAL_CAPACTIY
	if (capacity < capacityOnReserve)
		capacity = capacityOnReserve;

	//if attribs is nullptr then just allocate, otherwise allocate then copy
	if (attribs == nullptr) {
		attribs = new Attrib[capacity];
	} else {
		Attrib* copyBuffer = attribs;
		attribs = new Attrib[capacity];
		for(GLuint i = 0; i < length; i++)
			attribs[i] = copyBuffer[i];
		delete[] copyBuffer;
	}
	return canResize;
}

//Returns true if attribs array should be downsized
bool jlg::ShapeAttribs::DownSize() const {
	if(attribs == nullptr || capacity == 0)
		return false;
	if(((GLfloat)length/(GLfloat)capacity <= SHAPE_ATTRIBS_MIN_SPARSITY_RATIO) &&
		((capacity - length) >= SHAPE_ATTRIBS_MAX_FREE_SPACE) &&
		(capacity > capacityOnReserve))
		return true;
	else
		return false;
}

//Creates new Attrib struct and appends it to the end of attribs array. If AtMaxCapacity is true then no action is taken.
//Returns true if Attrib was successfully added to attribs array
bool jlg::ShapeAttribs::InsertAttrib(
	const GLuint& Index,
	const GLuint& Count,
	const GLuint& Stride,
	const GLuint& Offset) {
	if (AtMaxCapacity()) {
		std::cerr << "WARNING::SHAPE ATTRIBS::INSERT ATTRIB::ShapeAttrib is at Max Capacity. Remove Attribs using PopBack before inserting more attributes. Alternatively, replace attribs currently in container using operator[](const GLuint& Index)" << std::endl;
		return false;
	}
	if (length >= capacity)
		Resize();
	attribs[length] = Attrib(Index, Count, Stride, Offset);
	length++;
	return true;
}
//Internal method used to update capacityOnReserve.
//This method should be used to update capacityOnReserve opposed to direct assignment.
//This method will also allocate space if needed.
void jlg::ShapeAttribs::SetAndValidateReserveCapacity(const GLuint& ReserveCapacity) {
	if (ReserveCapacity > 0 && ReserveCapacity <= SHAPE_ATTRIBS_MAX_CAPACITY) {
		capacityOnReserve = ReserveCapacity;
		if(capacity < capacityOnReserve)
			Resize(capacityOnReserve);
	} else if (ReserveCapacity > SHAPE_ATTRIBS_MAX_CAPACITY) {
		std::cerr << "WARNING::SHAPE_ATTRIBS::SET_AND_VALIDATE_RESERVE_CAPACITY::Reserve Capacity argument excceds max capacity limit. Capacity on reserve has been set to max capacity limit." << std::endl;
		capacityOnReserve = SHAPE_ATTRIBS_MAX_CAPACITY;
		if (capacity < capacityOnReserve)
			Resize(capacityOnReserve);
	} else {
		capacityOnReserve = 0;
	}
}

//Internal method used to validate a ShapeAttribs object before copy, move, or assignment
bool jlg::ShapeAttribs::IsOkayToCopyOrMove(const ShapeAttribs& AttribObj) const {
	bool result = true;
	//check length
	if (AttribObj.length < 0 || AttribObj.length > SHAPE_ATTRIBS_MAX_CAPACITY) {
		std::cerr << "ERROR::SHAPE_ATTRIBS::COPY_MOVE_OR_ASSIGN::ShapeAttrib object length is outside min/max limits" << std::endl;
		result = false;
	}
	if (AttribObj.length > AttribObj.capacity) {
		std::cerr << "ERROR::SHAPE_ATTRIBS::COPY_MOVE_OR_ASSIGN::ShapeAttrib object length cannot be greater than the capacity" << std::endl;
		result = false;
	}
	if (AttribObj.capacity < 0 || AttribObj.capacity > SHAPE_ATTRIBS_MAX_CAPACITY) {
		std::cerr << "ERROR::SHAPE_ATTRIBS::COPY_MOVE_OR_ASSIGN::ShapeAttrib object capacity is outside min/max limits" << std::endl;
		result = false;
	}
	if (AttribObj.capacityOnReserve < 0 || AttribObj.capacityOnReserve > SHAPE_ATTRIBS_MAX_CAPACITY) {
		std::cerr << "ERROR::SHAPE_ATTRIBS::COPY_MOVE_OR_ASSIGN::ShapeAttrib object capacityOnReserve is outside min/max limits" << std::endl;
		result = false;
	}
	if (AttribObj.length > 0 && AttribObj.attribs == nullptr) {
		std::cerr << "ERROR::SHAPE_ATTRIBS::COPY_MOVE_OR_ASSIGN::ShapeAttrib object has contradicting members. Length is greater than zero, but attribs array is null." << std::endl;
		result = false;
	}
	return result;
}

//Internal method used copy a ShapeAttribs object. Calls IsOkayToCopyOrMove. Returns false if copy did not occur due to invalid data.
bool jlg::ShapeAttribs::Copy(const ShapeAttribs& AttribsObj) {
	if(!IsOkayToCopyOrMove(AttribsObj))
		return false;
	length = AttribsObj.length;
	capacity = AttribsObj.capacity;
	capacityOnReserve = AttribsObj.capacityOnReserve;
	attribs = nullptr;
	if (capacity < capacityOnReserve)
		capacity = capacityOnReserve;
	attribs = new Attrib[capacity];
	for (GLuint i = 0; i < length; i++)
		attribs[i] = AttribsObj.attribs[i];
	return true;
}


//Initialize all to zero. Does not perform memory allocation.
jlg::ShapeAttribs::ShapeAttribs() :
	length(0),
	capacity(0),
	capacityOnReserve(0),
	attribs(nullptr) {}

//Allocates space per ReserveCapacity arg. Initializes capacity to ReserveCapacity.
jlg::ShapeAttribs::ShapeAttribs(const GLuint& ReserveCapacity) :
	length(0),
	capacity(0),
	capacityOnReserve(0),
	attribs(nullptr) {
	SetAndValidateReserveCapacity(ReserveCapacity);
}

//Allocates space and copies Attrib structs from CopyAttribs. No allocation is performed if CopyAttribs is empty.
jlg::ShapeAttribs::ShapeAttribs(const ShapeAttribs& CopyAttribs) :
	length(0),
	capacity(0),
	capacityOnReserve(0),
	attribs(nullptr) {
	if(!Copy(CopyAttribs))
		throw std::exception("Attempt to copy invalid ShapeAttribs object");

}
//Allocates space and moves Attrib structs from MoveAttribs. If Move attribs is empty no allocation is performed. Releases MoveAttribs attribs array, sets pointer to nullptr and sets capacity and length to zero.
jlg::ShapeAttribs::ShapeAttribs(ShapeAttribs&& MoveAttribs) :
	length(0),
	capacity(0),
	capacityOnReserve(0),
	attribs(nullptr) {
	if (!IsOkayToCopyOrMove(MoveAttribs))
		throw std::exception("Attempt to move invalid ShapeAttribs object");
	length = std::move(MoveAttribs.length);
	capacity = std::move(MoveAttribs.capacity);
	capacityOnReserve = std::move(MoveAttribs.capacityOnReserve);
	attribs = nullptr;
	if (capacity < capacityOnReserve)
		capacity = capacityOnReserve;
	attribs = new Attrib[capacity];
	if (MoveAttribs.attribs != nullptr) {
		for (GLuint i = 0; i < length; i++)
			attribs[i] = std::move(MoveAttribs.attribs[i]);
		Attrib* delPtr = MoveAttribs.attribs;
		MoveAttribs.attribs = nullptr;
		delete[] delPtr;
	}
	MoveAttribs.length = 0;
	MoveAttribs.capacity = 0;
	MoveAttribs.capacityOnReserve = 0;
}

//Ensures resources are released.
jlg::ShapeAttribs::~ShapeAttribs() {

	if (attribs != nullptr) {
		Attrib* delPtr = attribs;
		attribs = nullptr;
		delete[] delPtr;
	}
}

//Releases any memory allocated to data.vertexData and resets members to zero or nullptr
void jlg::Shape::ClearVertexData() {
	if (data.vertexData.vertices != nullptr) {
		GLfloat* delPtr = data.vertexData.vertices;
		data.vertexData.vertices = nullptr;
		delete[] delPtr;
	}
	data.vertexData.count = 0;
	data.vertexData.dims = 0;
	data.vertexData.size = 0;
	data.vertexData.length = 0;
}

//Clears vertexData struct (call to ClearVertexData) then sets vertexData struct members per arguments.
void jlg::Shape::ResetVertexData(const GLfloat* VertexArray, const GLuint& Count, const GLuint& Dimensions) {
	ClearVertexData();
	data.vertexData.count = Count;
	data.vertexData.dims = Dimensions;
	data.vertexData.length = Count * Dimensions;
	data.vertexData.size = data.vertexData.length * sizeof(GLfloat);
	data.vertexData.vertices = new GLfloat[data.vertexData.length];
	for(GLuint i = 0; i < data.vertexData.length; i++)
		data.vertexData.vertices[i] = VertexArray[i];

}

jlg::Shape::Shape() {}
jlg::Shape::Shape(const Shape& CopyShape) : data(CopyShape.data) {}
jlg::Shape::Shape(Shape&& MoveShape) : data(std::move(MoveShape.data)) {}
jlg::Shape::Shape(const ShapeData& InitShapeData) : data(InitShapeData) {}
jlg::Shape::Shape(const VertexData& InitVertexData) : data(InitVertexData)  {}
jlg::Shape::Shape(const ShapeAttribs& InitShapeAttribs) : data(InitShapeAttribs) {}
jlg::Shape::Shape(const VertexData& InitVertexData, const ShapeAttribs& InitShapeAttribs) :
	data(InitVertexData, InitShapeAttribs) {}

void jlg::Shape::BufferVertexAttributes() {
	for (GLuint i = 0; i < data.attributes.Length(); i++) {
		glVertexAttribPointer(
			data.attributes[i].index,
			data.attributes[i].count,
			GL_FLOAT,
			GL_FALSE,
			data.attributes[i].stride * sizeof(GLfloat), (GLvoid*)(data.attributes[i].offset * sizeof(GLfloat)));
		glEnableVertexAttribArray(data.attributes[i].index);
	}
}

