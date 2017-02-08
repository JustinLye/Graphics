#include"jlg/callbacks.h"

std::vector<jlg::cb_key> jlg::cb_mgr::_subscribers;

void jlg::cb_mgr::subscribe(wptr callback_context, JLGenum callback_type, void* callback_function) {
	_subscribers.push_back(cb_key(callback_context, callback_type, callback_function));
}

void jlg::cb_mgr::keycb(wptr window, int key, int scancode, int action, int mode) {
	cb_key temp_key(window, JLG_CBFUN_KEYBOARD_INPUT, nullptr);
	keyboard_wrapper temp_w(&temp_key, key, scancode, action, mode);
	for (int i = 0; i < _subscribers.size(); i++) {
		if (temp_key.equal_keys(_subscribers[i])) {
			temp_w.call_key->cb_funct = _subscribers[i].cb_funct;
			temp_w.invoke();
		}
	}
}

void jlg::cb_mgr::bind_context(wptr context_handle, JLGenum callback_type) {
	switch (callback_type) {
	case JLG_CBFUN_KEYBOARD_INPUT:
		glfwMakeContextCurrent(context_handle);
		glfwSetKeyCallback(context_handle, keycb);
		break;
	};
}