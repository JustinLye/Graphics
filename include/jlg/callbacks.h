#include<iostream>
#include<set>
#if !defined(__JLG_CALLBACKS_HEADER__)
#define __JLG_CALLBACKS_HEADER__

#include"jlg/base/camera.h"

namespace jlg {
	enum {
		JLG_CBFUN_UNKNOWN = 0,
		JLG_CBFUN_KEYBOARD_INPUT = 1,
		JLG_CBFUN_MOUSE_MOVE = 2,
		JLG_CBFUN_MOUSE_SCROLL = 3
	};

#if !defined(__JLG_GLFWWINDOWPTR_TYPEDEF__)
#define __JLG_GLFWWINDOWPTR_TYPEDEF__
	typedef GLFWwindow* wptr;
#endif

#if !defined(__JLG_JLGENUM_TYPEDEF__)
	typedef unsigned int JLGenum;
#endif


	struct cb_key {
		wptr cb_context;
		GLenum cb_type;
		void* cb_funct;
		cb_key() :
			cb_context(nullptr),
			cb_type(JLG_CBFUN_UNKNOWN),
			cb_funct(nullptr) {}
		cb_key(
			wptr context_handle,
			GLenum callback_type,
			void* callback_function) :
			cb_context(context_handle),
			cb_type(callback_type),
			cb_funct(callback_function) {}
		inline bool equal_keys(const cb_key& other) const {
			return (cb_context == other.cb_context && cb_type == other.cb_type);
		}
		inline bool operator<(const cb_key& other) const {
			if (cb_context != other.cb_context)
				return cb_context < other.cb_context;
			if (cb_type != other.cb_type)
				return cb_type < other.cb_type;
			if (cb_funct == other.cb_funct) {
				return false;
			} else {
				if (cb_funct == nullptr)
					return true;
				return cb_funct < other.cb_funct;
			}
		}
	};

	class cb_wrapper {
	public:
		cb_key* call_key;
		cb_wrapper() :
			call_key(nullptr) {}
		cb_wrapper(cb_key* key_ptr) :
			call_key(key_ptr) {}
		virtual void invoke() = 0;
	};


	class keyboard_wrapper : public cb_wrapper {
	public:
		keyboard_wrapper() :
			cb_wrapper() {}
		keyboard_wrapper(
			cb_key* callback_key,
			int key,
			int scancode,
			int action,
			int mode) :
			cb_wrapper(callback_key),
			_key(key),
			_scancode(scancode),
			_action(action),
			_mode(mode) {}
		void invoke() {
			(((void(*)(wptr,int,int,int,int))(call_key->cb_funct))(call_key->cb_context, _key, _scancode, _action, _mode));
		}
	protected:
		int _key, _scancode, _action, _mode;
	};

	class cb_mgr {
	public:
		static void subscribe(wptr callback_context, JLGenum callback_type, void* callback_function);
		static void keycb(wptr window, int key, int scancode, int action, int mode);
		static void bind_context(wptr context_handle, JLGenum callback_type);
	protected:
		static std::vector<cb_key> _subscribers;
		
	};


};

#endif