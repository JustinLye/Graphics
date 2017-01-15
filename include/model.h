#if !defined(__JLG_MODEL_HEADER__)
#define __JLG_MODEL_HEADER__

#include"texture.h"
#include"shapes.h"

namespace jlg {
	class Model {
	public:
		Texture texture;
		Cube cube;
		Model();

	};
};


#endif