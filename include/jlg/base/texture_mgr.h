

#include"jlg/base/texture.h"
#include<vector>
#if !defined(__JLG_TEXTURE_MANAGER_HEADER__)
#define __JLG_TEXTURE_MANAGER_HEADER__
namespace jlg {
	class texture_mgr {
	public:
		texture_mgr();
		virtual GLuint add_texture(
			const char* image_file_path,
			const char* texture_name,
			const GLuint& program_id,
			const GLuint& unit_id);
		virtual void activate_texture(const GLuint& texture_id);
		virtual void set_uniform(const GLuint& texture_id);
		virtual void set_uniform();
		virtual inline void clear() {
			_textures.clear();
			_next_index = 0;
		}
	protected:
		std::vector<jlg::texture_unit> _textures;
	private:
		GLuint _next_index;
	};
};
#endif