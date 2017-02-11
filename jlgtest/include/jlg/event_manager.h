#include<iostream>
#include<set>
#if !defined(GLEW_STATIC)
#define GLEW_STATIC
#endif
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#if !defined(__JLG_EVENT_MANAGER_HEADER__)
#define __JLG_EVENT_MANAGER_HEADER__

namespace jlg {
	enum {
		JLG_EVENT_TYPE_UNKNOWN,
		JLG_EVENT_TYPE_KEY_INPUT,
		JLG_EVENT_TYPE_MOUSE_MV,
		JLG_EVENT_TYPE_MOUSE_SCROLL
	};
#if !defined(__JLG_EVENT_TYPE__)
#define __JLG_EVENT_TYPE__
	typedef const GLuint& JLG_event_type;
#endif
	static const GLuint& GetEventKey(GLFWwindow* window, JLG_event_type et) { return window == nullptr ? et : (GLuint)window + et; }
	class event_key {
	protected:
		GLuint _id;
		
		
		
		void output(std::ostream& s) const {
			s << "Window: " << _window << " Event Type: " << _event_type << " Callback: " << _cb;
		}
	public:
		GLFWwindow* _window;
		JLG_event_type _event_type;
		void* _cb;
		event_key(GLFWwindow* wind, JLG_event_type et, void* cb) : _window(wind), _event_type(et), _id(wind == nullptr ? et : (GLuint)wind + et), _cb(cb) {}
		event_key() : _window(nullptr), _event_type(JLG_EVENT_TYPE_UNKNOWN), _id(0), _cb(nullptr) {}
		inline bool operator<(const event_key& other) const { return _id < other._id; }
		inline bool operator<=(const event_key& other) const { return _id <= other._id; }
		inline bool operator==(const event_key& other) const { return _id == other._id; }
		inline bool operator!=(const event_key& other) const { return _id != other._id; }
		inline bool operator>=(const event_key& other) const { return _id >= other._id; }
		inline bool operator>(const event_key& other) const { return _id > other._id; }

		inline bool operator<(const GLuint& other) const { return _id < other; }
		inline bool operator<=(const GLuint& other) const { return _id <= other; }
		inline bool operator==(const GLuint& other) const { return _id == other; }
		inline bool operator!=(const GLuint& other) const { return _id != other; }
		inline bool operator>=(const GLuint& other) const { return _id >= other; }
		inline bool operator>(const GLuint& other) const { return _id > other; }
		inline friend std::ostream& operator<<(std::ostream& s, const event_key& e) {
			e.output(s);
			return s;
		}

	};

	class event_manager {
		
	public:
		static std::set<event_key> _subscribers;
		static void Subscribe(GLFWwindow* win, JLG_event_type et, void* cb);
		static void key_callback(GLFWwindow* win, int key, int action, int scancode, int mode);
	};
};

#endif
