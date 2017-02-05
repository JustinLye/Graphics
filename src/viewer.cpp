#include"../include/viewer.h"

jlg::viewer::viewer(
	const GLuint& Width,
	const GLuint& Height,
	const GLchar* Title,
	const GLchar* Vertex_Shader_Path,
	const GLchar* Fragment_Shader_Path) :
	_window(Width, Height, Title),
	_shader(Vertex_Shader_Path, Fragment_Shader_Path) {
	_window.SetViewport();
}