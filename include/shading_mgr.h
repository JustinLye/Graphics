#if !defined(__JLG_SHADING_MANAGER_HEADER__)
#define __JLG_SHADING_MANAGER_HEADER__
#include"camera_mgr.h"
#include"texture_shader.h"

namespace jlg {
	class basic_shading_mgr : public texture_shader {
	public:
		basic_shading_mgr();
		basic_shading_mgr(const char* vertex_shader_path, const char* fragment_shader_path);
		virtual void apply(
			const char* model_lbl = "model",
			const char* view_lbl = "view",
			const char* proj_lbl = "projection");
	};
};

#endif