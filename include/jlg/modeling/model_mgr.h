#include<vector>
#if !defined(__JLG_MODEL_MANAGER_HEADER__)
#define __JLG_MODEL_MANAGER_HEADER__

#include"model.h"

namespace jlg {
	class model_mgr {
	public:
		model_mgr();
		virtual void add_model(
			GLuint& model_id,
			const GLfloat* data,
			const GLuint& dimensions,
			const GLuint& vertex_count,
			const glm::vec3& init_position = glm::vec3(0.0f, 0.0f, 0.0f),
			const GLfloat& init_angle = 0.0f,
			const glm::vec3& init_rotation_axis = glm::vec3(0.0f, 0.0f, 0.0f));
		virtual void add_attrib(const GLuint& model_id, const GLuint& Count);
		virtual void buffer();
		virtual void draw() const;
		virtual const GLuint& count() const { return (GLuint)_models.size(); }
		virtual inline jlg::model& operator[](int model_id) {
			return _models[model_id];
		}
	protected:
		std::vector<jlg::model> _models;
		std::vector<GLuint> _buffer_objs;
		std::vector<GLuint> _vertex_buffer_array_objs;
	};
};

#endif