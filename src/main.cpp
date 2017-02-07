
#include<jlg/jlg.h>

int main(int argc, char* argv[]) {
	jlg::model_viewer win(800, 600, "Window","shaders\\core.vs", "shaders\\core.frag");
	win.window().SetColor(0.1f, 0.3f, 0.3f, 1.0f);
	win.window().lock_cursor();
	win.shader().add_texture("images\\container.jpg", "texture_01");
	GLuint model_id;
	win.models().add_model(
		model_id,
		jlg::JLG_SHAPE_3D_CUBE_VERTS, 
		jlg::
	return EXIT_SUCCESS;
}



