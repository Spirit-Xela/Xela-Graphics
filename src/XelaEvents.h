#ifndef _XELA_EVENTS_H
#define _XELA_EVENTS_H

//Engine
#include "XelaWindow.h"
#include "XelaDefinitions.h"
//C++
#ifdef XELA_DEBUG_EVENTS
	#include <iostream>
#endif
#include <unordered_map>

struct KeyInfo {
	int key, scancode, action, mods;
	XelaWindow *window;
};
struct MouseButtonInfo {
	int button, action, mods;
	XelaWindow *window;
};
struct CursorPosInfo {
	double xpos, ypos;
	XelaWindow *window;
};

typedef void(*XelaKeyCallback)(XelaWindow *window, int key, int scancode, int action, int mods);
typedef void(*XelaMouseButtonCallback)(XelaWindow *window, int button, int action, int mods);
typedef void(*XelaCursorPosCallback)(XelaWindow *window, double xpos, double ypos);

//Used to keep track of which XelaWindow corresponds to which GLFWwindow.
void xelaAddWindow(GLFWwindow *key, XelaWindow *window);

//Adds information about a key event to the buffer to be processed when xelaProcessEvents() is called.
//If info.action == XELA_RELEASE, then this key will be removed from the buffer after being processed.
void xelaAddKeyToBuffer(KeyInfo info);
//Adds information about a mouse event to the buffer to be processed when xelaProcessEvents() is called.
//If info.action == XELA_RELEASE, then this will be removed from the buffer after being processed.
void xelaAddMouseToBuffer(MouseButtonInfo info);

//Calls the corresponding cursorPos callback function.
void xelaUpdateCursorPos(CursorPosInfo info);

//Process buffered key/mouse events
void xelaProcessEvents();

//Set a function to be called to respond to key events.
void xelaSetKeyCallback(XelaKeyCallback cb);
//Set a function to be called to respond to mouse button events.
void xelaSetMouseButtonCallback(XelaMouseButtonCallback cb);
//Set a function to be called to respond to cursor position events.
void xelaSetCursorPosCallback(XelaCursorPosCallback cb);

//Returns the XelaWindow associated with a given GLFWwindow
XelaWindow* getXelaWindow(GLFWwindow *key);

#endif