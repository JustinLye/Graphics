
#if !defined(__JLG_BASE_HEADER__)
#define __JLG_BASE_HEADER__
#include"base/camera_mgr.h"
#include"base/shader.h"
#include"base/shape_mgr.h"
#include"base/texture_mgr.h"
#include"base/window.h"

#if !defined(__JLG_SHADER_SRC_STD__)
#define __JLG_SHADER_SRC_STD__
namespace jlg {
	const GLuint JLG_SHAPE_3D_CUBE_DIMS = 5;
	const GLuint JLG_SHAPE_3D_CUBE_COUNT = 36;
	const GLfloat JLG_SHAPE_3D_CUBE_VERTS[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	inline const vertex_data& jlg_vertex_data_cube() {
		return jlg::vertex_data(JLG_SHAPE_3D_CUBE_VERTS, JLG_SHAPE_3D_CUBE_DIMS, JLG_SHAPE_3D_CUBE_COUNT);
	}
	const GLuint JLG_SHAPE_2D_TRIANGLE_DIMS = 3;
	const GLuint JLG_SHAPE_2D_TRIANGLE_COUNT = 3;
	const GLfloat JLG_SHAPE_2D_TRIANGLE_VERTS[] = {
		-0.5f, -0.25f, 0.0f,
		0.5f, -0.25f, 0.0f,
		0.0f, 0.25f, 0.0f
	};
	inline const shape& jlg_shape_cube() {
		shape cube(JLG_SHAPE_3D_CUBE_VERTS, JLG_SHAPE_3D_CUBE_DIMS, JLG_SHAPE_3D_CUBE_COUNT);
		cube.add_attrib(3);
		cube.add_attrib(2);
		return cube;
	}
	void add_cube(GLuint& shape_id, shape_mgr* shape_manager) {
		shape_manager->add_shape(shape_id, JLG_SHAPE_3D_CUBE_VERTS, JLG_SHAPE_3D_CUBE_DIMS, JLG_SHAPE_3D_CUBE_COUNT);
		shape_manager->add_shape_attrib(shape_id, 3);
		shape_manager->add_shape_attrib(shape_id, 2);
	}
	void add_triangle(GLuint& shape_id, shape_mgr* shape_manager) {
		shape_manager->add_shape(shape_id, JLG_SHAPE_2D_TRIANGLE_VERTS, JLG_SHAPE_2D_TRIANGLE_DIMS, JLG_SHAPE_2D_TRIANGLE_COUNT);
		shape_manager->add_shape_attrib(shape_id, 3);
	}
};
#endif

#endif