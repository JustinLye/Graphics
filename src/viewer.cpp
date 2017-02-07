#include"jlg/viewing/viewer.h"

jlg::viewer::viewer(
	const GLuint& Width,
	const GLuint& Height,
	const GLchar* Title,
	const GLchar* Vertex_Shader_Path,
	const GLchar* Fragment_Shader_Path) :
	_window(Width, Height, Title),
	_shader(Vertex_Shader_Path, Fragment_Shader_Path),
	_camera(glm::vec3(0.0f, 0.0f, 3.0f)),
	_current_frame(0.0f),
	_last_frame(0.0f),
	_delta_time(0.0f) {
	_window.SetViewport();
	jlg::camera_mgr::bind_camera(&_camera, _window.Handle());
}


jlg::model_viewer::model_viewer(
	const GLuint& Width,
	const GLuint& Height,
	const GLchar* Title,
	const GLchar* Vertex_Shader_Path,
	const GLchar* Fragment_Shader_Path) :
	_camera(glm::vec3(0.0f, 0.0f, 3.0f)),
	_current_frame(0.0f),
	_last_frame(0.0f),
	_delta_time(0.0f),
	_window(Width, Height, Title),
	_shader(Vertex_Shader_Path, Fragment_Shader_Path) {
	_window.SetViewport();
	jlg::camera_mgr::bind_camera(&_camera, _window.Handle(), Width, Height);
	_shader.set_model_manager(&this->_models);
}
	