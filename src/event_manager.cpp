#include"jlg/event_manager.h"

std::set<jlg::event_key> jlg::event_manager::_subscribers;

void jlg::event_manager::Subscribe(GLFWwindow* win, JLG_event_type et, void* cb) {
	_subscribers.insert(jlg::event_key(win, et, cb));
}

void jlg::event_manager::key_callback(GLFWwindow* win, int key, int action, int scancode, int mode) {
	auto ev = _subscribers.find(jlg::event_key(win, jlg::JLG_EVENT_TYPE_KEY_INPUT, nullptr));
	((void(*)(GLFWwindow*,int,int,int,int))ev->_cb)(win, key, action, scancode, mode);

}