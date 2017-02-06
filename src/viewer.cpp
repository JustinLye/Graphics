#include"../include/viewer.h"

jlg::viewer::viewer(
	const GLuint& Width,
	const GLuint& Height,
	const GLchar* Title,
	const GLchar* Vertex_Shader_Path,
	const GLchar* Fragment_Shader_Path) :
	window(Width, Height, Title),
	shader(Vertex_Shader_Path, Fragment_Shader_Path),
	_camera(glm::vec3(0.0f, 0.0f, 3.0f)),
	_current_frame(0.0f),
	_last_frame(0.0f),
	_delta_time(0.0f) {
	window.SetViewport();
	jlg::camera_mgr::bind_camera(&_camera, window.Handle());
}
