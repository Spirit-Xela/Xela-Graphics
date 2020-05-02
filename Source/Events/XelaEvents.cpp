//Xela Graphics
#include "XelaEvents.h"

//C++
#if XELA_DEBUG_EVENTS
#include <iostream>
#endif
#include <unordered_map>

//List of key events to be processed.
static std::unordered_map<int, XelaKeyInfo> keyBuffer;
//List of mouse button events to be processed.
static std::unordered_map<int, XelaMouseButtonInfo> mouseBuffer;
//List of GLFWwindows and their associated XelaWindows.
static std::unordered_map<GLFWwindow *, XelaWindow *> windowList;

//Function to be called to process key events.
static XelaKeyCallback keyCB = nullptr;
//Function to be called to process mouse button events.
static XelaMouseButtonCallback mouseButtonCB = nullptr;
//Function to be called to process cursor position events.
static XelaCursorPosCallback cursorPosCB = nullptr;
//Function to be called whenever a window is resized
static XelaWindowSizeCallback windowSizeCB = nullptr;

void xelaAddWindow(GLFWwindow *key, XelaWindow *window) {
	windowList.emplace(key, window);
}

void xelaAddKeyToBuffer(XelaKeyInfo info) {
	if (keyBuffer.count(info.key)) {
		//Key already exists, update data.
		keyBuffer.at(info.key) = info;
	}
	else {
		//Key does not exist, emplace data.
		keyBuffer.emplace(info.key, info);
	}
	#if XELA_DEBUG_EVENTS
	//Print key.
	std::cout << "[Message][XelaEvents] Added key to KeyBuffer: " << info.key << std::endl;
	#endif
}
void xelaAddMouseToBuffer(XelaMouseButtonInfo info) {
	if (mouseBuffer.count(info.button)) {
		//Key already exists, update data.
		mouseBuffer.at(info.button) = info;
	}
	else {
		//Key does not exist, emplace data.
		mouseBuffer.emplace(info.button, info);
	}
	#if XELA_DEBUG_EVENTS
	//Print key.
	std::cout << "[Message][XelaEvents] Added mouse button to MouseBuffer: " << info.key << std::endl;
	#endif
}
void xelaUpdateCursorPos(XelaCursorPosInfo info) {
	if (cursorPosCB != nullptr) {
		cursorPosCB(info.window, info.xpos, info.ypos);
	}
	#if XELA_DEBUG_EVENTS
	//Print button.
	std::cout << "[Message][XelaEvents] Processed cursor position: " << info.xpos << ", " << info.ypos << ", " << std::endl;
	#endif
}
void xelaUpdateWindowSize(XelaWindowSizeInfo info) {
	if (windowSizeCB != nullptr) {
		windowSizeCB(info.window, info.width, info.height);
	}
	#if XELA_DEBUG_EVENTS
	std::cout << "[Message][XelaEvents] Processed new window size: " << info.width << ", " << info.height << std::endl;
	#endif
}

static void xelagraphics_processKeys() {
	std::unordered_map<int, XelaKeyInfo>::iterator it = keyBuffer.begin(), tmp;
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
static void xelagraphics_processMouse() {
	std::unordered_map<int, XelaMouseButtonInfo>::iterator it = mouseBuffer.begin(), tmp;
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
void xelaGraphicsProcessEvents() {
	xelagraphics_processKeys();
	xelagraphics_processMouse();
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
void xelaSetWindowSizeCallback(XelaWindowSizeCallback cb) {
	windowSizeCB = cb;
}

XelaWindow *getXelaWindow(GLFWwindow *key) {
	if (windowList.count(key))
		return windowList.at(key);
	return nullptr;
}