#if !defined(__JLG_MODEL_HEADER__)
#define __JLG_MODEL_HEADER__
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"shapes.h"

namespace jlg {
	class Model {
	protected:
		Shape shape;
	public:
		glm::mat4 model_mat;
		glm::vec3 position;
		glm::vec3 rotationAxis;
		GLfloat rotationAngle;
		inline const glm::mat4& model() {
			model_mat = glm::translate(model_mat, position);
			model_mat = glm::rotate(model_mat, rotationAngle, rotationAxis);
			return model_mat;
		}
		inline void Buffer(const GLuint& VertexArrayObject, const GLuint& VertexBufferObject) {
			shape.Buffer(VertexArrayObject, VertexBufferObject);
		}
		inline void Draw() {
			shape.Draw();
		}

	};
};


#endif