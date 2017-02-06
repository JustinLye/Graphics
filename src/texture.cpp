#include"jlg/base/texture.h"

GLuint jlg::texture::_next_active_texture_id = GL_TEXTURE0;

jlg::texture::texture() :
	_is_generated(false),
	_image_file_path(nullptr) {}

jlg::texture::texture(const char* image_file_path, bool generate_now) :
	_is_generated(false),
	_image_file_path(image_file_path) {
	if(generate_now)
		load_texture(_image_file_path);
}

void jlg::texture::load_texture(const char* image_file_path) {
	bool pre_reqs = true;
	if (_is_generated) {
		std::cerr << "WARNING::TEXTURE::load_texture::No action was taken. An existing texture has been loaded." << std::endl;
		pre_reqs = false;
	}
	if (image_file_path == nullptr && _image_file_path == nullptr) {
		std::cerr << "ERROR::TEXTURE::load_texture::A file path to the image to be loaded must be provided." << std::endl;
		pre_reqs = false;
	}
	if(!pre_reqs)
		return;
	if(image_file_path != _image_file_path)
		_image_file_path = image_file_path;
	_generate_texture();
	_info.active_texture_id = _next_active_texture_id;
	_next_active_texture_id++;
}

void jlg::texture::_generate_texture() {
	glGenTextures(1, &_info.texture_id);
	glBindTexture(GL_TEXTURE_2D, _info.texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int w, h;
	unsigned char* image = SOIL_load_image(
		_image_file_path,
		&w,
		&h,
		0,
		SOIL_LOAD_RGB);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGB,
		w,
		h,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void jlg::texture::bind_texture() const {
	if (!_is_generated) {
		std::cerr << "ERROR::TEXTURE::bind_texture::Texture must be generated before binding can occur." << std::endl;
		return;
	}
	glActiveTexture(_info.active_texture_id);
	glBindTexture(GL_TEXTURE_2D, _info.texture_id);
}

jlg::texture_unit::texture_unit() :
	texture(),
	_name(nullptr) {}

jlg::texture_unit::texture_unit(
	const char* texture_name,
	const GLuint& texture_prog_id,
	const GLuint& texture_unit_id,
	const char* image_file_path,
	bool generate_now) :
	texture(image_file_path, generate_now),
	_name(texture_name),
	_program_id(texture_prog_id),
	_unit_id(texture_unit_id) {}