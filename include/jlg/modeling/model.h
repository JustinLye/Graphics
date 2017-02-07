#if !defined(__JLG_MODEL_HEADER__)
#define __JLG_MODEL_HEADER__

#include"jlg/base/shape.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

namespace jlg {
	class model : public shape {
	public:
		model(
			GLfloat* data,
			const GLuint& dimensions,
			const GLuint& vertex_count,
			const glm::vec3& init_position = glm::vec3(0.0f, 0.0f, 0.0f),
			const GLfloat& init_rotation_angle = 0.0f,
			const glm::vec3& init_rotation_axis = glm::vec3(0.0f, 0.0f, 0.0f));

		virtual inline void position(const glm::vec3& translation_vector) {
			_translation_vector = translation_vector;
		}
		virtual inline void rotation(const GLfloat& angle, const glm::vec3& rotation_axis_vector) {
			_rotation_angle = angle;
			_rotation_axis_vector = rotation_axis_vector;
		}
		virtual inline void rotation(const GLfloat& angle) {
			_rotation_angle = angle;
		}
		virtual inline void rotation(const glm::vec3& rotation_axis_vector) {
			_rotation_axis_vector = rotation_axis_vector;
		}
		virtual inline const glm::vec3& position() const { return _translation_vector; }
		virtual inline const GLfloat& rotation_angle() const { return _rotation_angle; }
		virtual inline const glm::vec3& rotation_axis() const { return _rotation_axis_vector; }
		virtual inline glm::mat4 transform() {
			_transform = glm::translate(glm::mat4(), _translation_vector);
			_transform = glm::rotate(_transform, _rotation_angle, _rotation_axis_vector);
			return _transform;
		}
		
	protected:
		glm::vec3 _translation_vector;
		glm::vec3 _rotation_axis_vector;
		GLfloat _rotation_angle;
		glm::mat4 _transform;
		static glm::mat4 _identity_matrix;
		
	};
};

#endif