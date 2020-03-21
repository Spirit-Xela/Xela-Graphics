#ifndef _XELA_EVENTS_H
#define _XELA_EVENTS_H

//Libs
#include "GL/glew.h"
#include "GLFW/glfw3.h"

//Xela Graphics
#include "XelaGraphics.h"
#include "XelaWindow.h"

struct XelaKeyInfo {
	int key, scancode, action, mods;
	XelaWindow *window;
};
struct XelaMouseButtonInfo {
	int button, action, mods;
	XelaWindow *window;
};
struct XelaCursorPosInfo {
	double xpos, ypos;
	XelaWindow *window;
};
struct XelaWindowSizeInfo {
	int width, height;
	XelaWindow *window;
};

typedef void(*XelaKeyCallback)(XelaWindow *window, int key, int scancode, int action, int mods);
typedef void(*XelaMouseButtonCallback)(XelaWindow *window, int button, int action, int mods);
typedef void(*XelaCursorPosCallback)(XelaWindow *window, double xpos, double ypos);
typedef void(*XelaWindowSizeCallback)(XelaWindow *window, int width, int height);

//Used to keep track of which XelaWindow corresponds to which GLFWwindow.
void xelaAddWindow(GLFWwindow *key, XelaWindow *window);

//Adds information about a key event to the buffer to be processed when xelaProcessEvents() is called.
//If info.action == XELA_RELEASE, then this key will be removed from the buffer after being processed.
void xelaAddKeyToBuffer(XelaKeyInfo info);
//Adds information about a mouse event to the buffer to be processed when xelaProcessEvents() is called.
//If info.action == XELA_RELEASE, then this will be removed from the buffer after being processed.
void xelaAddMouseToBuffer(XelaMouseButtonInfo info);

//Calls the corresponding cursorPos callback function.
void xelaUpdateCursorPos(XelaCursorPosInfo info);
//Calls the corresponding windowSize callback function
void xelaUpdateWindowSize(XelaWindowSizeInfo info);

//Process buffered key/mouse events
void xelaGraphicsProcessEvents();

extern "C" {
	//Set a function to be called to respond to key events.
	XELAGRAPHICS_API void xelaSetKeyCallback(XelaKeyCallback cb);
	//Set a function to be called to respond to mouse button events.
	XELAGRAPHICS_API void xelaSetMouseButtonCallback(XelaMouseButtonCallback cb);
	//Set a function to be called to respond to cursor position events.
	XELAGRAPHICS_API void xelaSetCursorPosCallback(XelaCursorPosCallback cb);
	//Set a function to be called whenever a window is resized
	XELAGRAPHICS_API void xelaSetWindowSizeCallback(XelaWindowSizeCallback cb);
}

//Returns the XelaWindow associated with a given GLFWwindow
XelaWindow *getXelaWindow(GLFWwindow *key);

#endif