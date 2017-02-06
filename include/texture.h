#include<iostream>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<SOIL2/SOIL2.h>

#if !defined(__JLG_TEXTURE_HEADER__)
#define __JLG_TEXTURE_HEADER__

namespace jlg {

	struct texture_info {
		GLuint texture_id;
		GLuint active_texture_id;
		const char* texture_name;
		texture_info() :
			texture_id(0),
			active_texture_id(0) {}
	};

	class texture {
	public:
		texture();
		texture(const char* image_file_path, bool generate_now = true);
		virtual void load_texture(const char* image_file_path = nullptr);
		inline const GLuint& id() const { return _info.texture_id; }
		inline const GLuint& active_id() const { return _info.active_texture_id; }
		inline const char* image_file_path() const { return _image_file_path; }
		inline bool is_generated() const { return _is_generated; }
		inline const GLuint& next_active_texture_id() const { return _next_active_texture_id; }
		virtual void bind_texture() const;
	protected:
		texture_info _info;
	private:
		bool _is_generated;
		const char* _image_file_path;
		static GLuint _next_active_texture_id;
		void _generate_texture();
	};

	class texture_unit : public texture {
	public:
		texture_unit();
		texture_unit(
			const char* texture_name,
			const GLuint& texture_prog_id,
			const GLuint& texture_unit_id,
			const char* image_file_path,
			bool generate_now = true);
		inline const char* name() const { return _name; }
		inline void name(const char* texture_name) { _name = texture_name; }
		inline const GLuint& program_id() const { return _program_id; }
		inline void program_id(const GLuint& texture_prog_id) { _program_id = texture_prog_id; }
		inline const GLuint& unit_id() const { return _unit_id; }
		inline void unit_id(const GLuint& texture_unit_id) { _unit_id = texture_unit_id; }
	protected:
		const char* _name;
		GLuint _program_id;
		GLuint _unit_id;
	};

	

};

#endif