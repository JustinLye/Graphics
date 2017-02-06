#include"model.h"

glm::mat4 jlg::model::_identity_matrix = glm::mat4();

jlg::model::model(
	GLfloat* data,
	const GLuint& dimensions,
	const GLuint& vertex_count,
	const glm::vec3& init_position,
	const GLfloat& init_rotation_angle,
	const glm::vec3& init_rotation_axis) :
	shape(data, dimensions, vertex_count),
	_translation_vector(init_position),
	_rotation_angle(init_rotation_angle),
	_rotation_axis_vector(init_rotation_axis) {}