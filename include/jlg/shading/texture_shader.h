#if !defined (__JLG_TEXTURE_SHADER_HEADER__)
#define __JLG_TEXTURE_SHADER_HEADER__

#include"jlg/base/shader.h"
#include"jlg/base/texture_mgr.h"

namespace jlg {
	class texture_shader {
	public:
		texture_shader();
		texture_shader(const char* vertex_shader_path, const char* fragment_shader_path);
		virtual GLuint add_texture(const char* image_file_path, const char* texture_name);
		inline void set_texture_uniform() { _texture_mgr.set_uniform(); }
		inline void clear_textures() { _texture_mgr.clear(); }
		inline GLuint program() { return _shader.program; }
		inline void use_program() const { _shader.use_program(); }
		inline void init_shader_program(const char* vertex_shader_path, const char* fragment_shader_path) {
			_shader.init_shader_program(vertex_shader_path, fragment_shader_path);
		}
		virtual inline void apply() { _shader.use_program(); _texture_mgr.set_uniform(); }
	protected:
		jlg::shader _shader;
		jlg::texture_mgr _texture_mgr;
	private:
		GLuint _next_unit_id;
		std::vector<GLuint> _texture_ids;


	};
};

#endif