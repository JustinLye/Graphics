#include"jlg/base/texture_mgr.h"

jlg::texture_mgr::texture_mgr() :
	_next_index(0) {}

GLuint jlg::texture_mgr::add_texture(
	const char* image_file_path,
	const char* texture_name,
	const GLuint& program_id,
	const GLuint& unit_id) {
	GLuint result = _next_index;
	_next_index++;
	_textures.push_back(jlg::texture_unit(texture_name, program_id, unit_id, image_file_path));
	return result;
}

void jlg::texture_mgr::activate_texture(const GLuint& texture_id) {
	glActiveTexture(_textures[texture_id].active_id());
	glBindTexture(GL_TEXTURE_2D, _textures[texture_id].id());
}


void jlg::texture_mgr::set_uniform(const GLuint& texture_id) {
	glActiveTexture(_textures[texture_id].active_id());
	glBindTexture(GL_TEXTURE_2D, _textures[texture_id].id());
	glUniform1i(
		glGetUniformLocation(
		_textures[texture_id].program_id(), 
		_textures[texture_id].name()),
		_textures[texture_id].unit_id());
}

void jlg::texture_mgr::set_uniform() {
	for (GLuint i = 0; i < _textures.size(); i++) {
		glActiveTexture(_textures[i].active_id());
		glBindTexture(GL_TEXTURE_2D, _textures[i].id());
		glUniform1i(
			glGetUniformLocation(
				_textures[i].program_id(),
				_textures[i].name()),
			_textures[i].unit_id());
	}
}