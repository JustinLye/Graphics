#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#if !defined(__JLG_SHADING_MANAGER_HEADER__)
#define __JLG_SHADING_MANAGER_HEADER__
#include"camera_mgr.h"
#include"texture_shader.h"
#include"model_mgr.h"
namespace jlg {
	class basic_shading_mgr : public texture_shader {
	public:
		basic_shading_mgr();
		basic_shading_mgr(const char* vertex_shader_path, const char* fragment_shader_path);
		virtual void apply(
			const char* view_lbl = "view",
			const char* proj_lbl = "projection",
			const char* model_lbl = "model");
		virtual void apply(glm::mat4& transform);
	};

	class model_shading_mgr : public texture_shader {
	public:
		model_shading_mgr();
		model_shading_mgr(const char* vertex_shader_path, const char* fragment_shader_path);
		model_shading_mgr(const char* vertex_shader_path, const char* fragment_shader_path, model_mgr* model_manager);
		inline virtual void set_model_manager(model_mgr* model_manager) { _model_mgr = model_manager; }
		virtual void apply();
	protected:
		model_mgr* _model_mgr;
	};

};

#endif