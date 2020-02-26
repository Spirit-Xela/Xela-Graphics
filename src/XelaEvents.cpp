#include "XelaEvents.h"

//List of key events to be processed.
std::unordered_map<int, KeyInfo> keyBuffer;
//List of mouse button events to be processed.
std::unordered_map<int, MouseButtonInfo> mouseBuffer;
//List of GLFWwindows and their associated XelaWindows.
std::unordered_map<GLFWwindow *, XelaWindow *> windowList;

//Function to be called to process key events.
XelaKeyCallback keyCB = nullptr;
//Function to be called to process mouse button events.
XelaMouseButtonCallback mouseButtonCB = nullptr;
//Function to be called to process cursor position events.
XelaCursorPosCallback cursorPosCB = nullptr;

void xelaAddWindow(GLFWwindow *key, XelaWindow *window) {
	windowList.emplace(key, window);
}

void xelaAddKeyToBuffer(KeyInfo info) {
	if (keyBuffer.count(info.key)) {
		//Key already exists, update data.
		keyBuffer.at(info.key) = info;
	}
	else {
		//Key does not exist, emplace data.
		keyBuffer.emplace(info.key, info);
	}
#ifdef XELA_DEBUG_EVENTS
	//Print key.
	std::cout << "[Message][XelaEvents] Added key to KeyBuffer: " << info.key << std::endl;
#endif
}
void xelaAddMouseToBuffer(MouseButtonInfo info) {
	if (mouseBuffer.count(info.button)) {
		//Key already exists, update data.
		mouseBuffer.at(info.button) = info;
	}
	else {
		//Key does not exist, emplace data.
		mouseBuffer.emplace(info.button, info);
	}
#ifdef XELA_DEBUG_EVENTS
	//Print key.
	std::cout << "[Message][XelaEvents] Added mouse button to MouseBuffer: " << info.key << std::endl;
#endif
}
void xelaUpdateCursorPos(CursorPosInfo info) {
	if (cursorPosCB != nullptr) {
		cursorPosCB(info.window, info.xpos, info.ypos);
	}
#ifdef XELA_DEBUG_EVENTS
	//Print button.
	std::cout << "[Message][XelaEvents] Processed cursor position: " << info.xpos << ", " << info.ypos << ", " << std::endl;
#endif
}

void processKeys() {
	std::unordered_map<int, KeyInfo>::iterator it = keyBuffer.begin(), tmp;
	while (it != keyBuffer.end()) {
		if (keyCB != nullptr) {
			keyCB(it->second.window, it->second.key, it->second.scancode, it->second.action, it->second.mods);
		}
		//Check for release.
		if (it->second.action == XELA_RELEASE) {
			//Don't repeat this event.
			tmp = it;
			tmp++;
			keyBuffer.erase(it);
			it = tmp;
		}
		else {
			it++;
		}
	}
}
void processMouse() {
	std::unordered_map<int, MouseButtonInfo>::iterator it = mouseBuffer.begin(), tmp;
	while (it != mouseBuffer.end()) {
		if (mouseButtonCB != nullptr) {
			mouseButtonCB(it->second.window, it->second.button, it->second.action, it->second.mods);
		}
		//Check for release.
		if (it->second.action == XELA_RELEASE) {
			//Don't repeat this event.
			tmp = it;
			tmp++;
			mouseBuffer.erase(it);
			it = tmp;
		}
		else {
			it++;
		}
	}
}
void xelaProcessEvents() {
	processKeys();
	processMouse();
}

void xelaSetKeyCallback(XelaKeyCallback cb) {
	keyCB = cb;
}
void xelaSetMouseButtonCallback(XelaMouseButtonCallback cb) {
	mouseButtonCB = cb;
}
void xelaSetCursorPosCallback(XelaCursorPosCallback cb) {
	cursorPosCB = cb;
}

XelaWindow* getXelaWindow(GLFWwindow *key) {
	if (windowList.count(key))
		return windowList.at(key);
	return nullptr;
}