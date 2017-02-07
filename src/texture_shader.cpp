#include"jlg/shading/texture_shader.h"

jlg::texture_shader::texture_shader() :
	_next_unit_id(0) {}
jlg::texture_shader::texture_shader(const char* vertex_shader_path, const char* fragment_shader_path) :
	_next_unit_id(0),
	_shader(vertex_shader_path, fragment_shader_path) {}
GLuint jlg::texture_shader::add_texture(const char* image_file_path, const char* texture_name) {
	if (!_shader.is_initialized()) {
		std::cerr << "WARNING::TEXTURE SHADER::add_texture::No action taken because shader program has not been initialized." << std::endl;
		return 0;
	}
	_texture_ids.push_back(
		_texture_mgr.add_texture(
			image_file_path,
			texture_name,
			_shader.program,
			_next_unit_id));
	_next_unit_id++;
	return _texture_ids.size() - 1;
}