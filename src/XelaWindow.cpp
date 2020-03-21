//Xela Graphics
#include "XelaWindow.h"
#include "XelaGraphicsInit.h"
#include "XelaEvents.h"
#include "XelaCallbacks.h"

//C++
#if XELA_DEBUG_WINDOW
#include <iostream>
#endif

XelaWindow *XelaWindow::genWindow(int sizeX, int sizeY, const char *title, bool fullscreen, int *success, bool decorated, XelaWindow *share) {
	XelaWindow *win = new XelaWindow();

	int errCode, windowSizeX, windowSizeY;
	const char *errMsg;
	win->winTitle = title;

	//Initialize library.
	if (xelaGraphicsInit()) {
		*success = XELA_SUCCESS;
	}
	else {
		*success = XELA_ERROR_INIT;
		#if XELA_DEBUG_WINDOW
		//Print error.
		std::cout << "[ERROR][XelaWindow] Error initializing engine" << std::endl;
		#endif
		return nullptr;
	}
	//Create a window object.
	win->glfwMonitor = glfwGetPrimaryMonitor();
	win->mode = glfwGetVideoMode(win->glfwMonitor);
	if (sizeX < 0) {
		sizeX = win->mode->width;
	}
	if (sizeY < 0) {
		sizeY = win->mode->height;
	}
	glfwWindowHint(GLFW_DECORATED, decorated);
	win->glfwWindow = glfwCreateWindow(sizeX, sizeY, title, fullscreen ? win->glfwMonitor : NULL, share == nullptr ? NULL : share->glfwWindow);
	if (win->glfwWindow == NULL) {
		//Error occurred.
		#if XELA_DEBUG_WINDOW
				//Print error.
		errCode = glfwGetError(&errMsg);
		std::cout << "[ERROR][XelaWindow] GLFW Error occurred on window creation (" << errCode << "): " << errMsg << std::endl;
		#endif
		*success = XELA_ERROR_WINDOW;
		return nullptr;
	}
	glfwMakeContextCurrent(win->glfwWindow);
	glfwSwapInterval(1);
	//Setup callback functions.
	xelaGraphicsInitCallbacks(win->glfwWindow);
	glfwGetFramebufferSize(win->glfwWindow, &windowSizeX, &windowSizeY);
	glViewport(0, 0, windowSizeX, windowSizeY);
	#if XELA_DEBUG_WINDOW
	std::cout << "[Message][XelaInit] Initialized callback functions" << std::endl;
	#endif
	#if XELA_DEBUG_WINDOW
	//Print window attributes.
	std::cout << "[Mesaage][XelaWindow] Window created with the following configuration: " << std::endl;
	std::cout << "[Message][XelaWindow] ===>| Size: " << sizeX << ", " << sizeY << std::endl;
	std::cout << "[Message][XelaWindow] ===>| Title: " << title << std::endl;
	std::cout << "[Message][XelaWindow] ===>| Fullscreen: " << fullscreen << std::endl;
	std::cout << "[Message][XelaWindow] Window created with the following GLFW attributes: " << std::endl;
	std::cout << "[Message][XelaWindow] ===>| Window related attributes: " << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Focused: " << glfwGetWindowAttrib(win->glfwWindow, GLFW_FOCUSED) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Iconified: " << glfwGetWindowAttrib(win->glfwWindow, GLFW_ICONIFIED) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Maximized: " << glfwGetWindowAttrib(win->glfwWindow, GLFW_MAXIMIZED) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Hovered: " << glfwGetWindowAttrib(win->glfwWindow, GLFW_HOVERED) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Visible: " << glfwGetWindowAttrib(win->glfwWindow, GLFW_VISIBLE) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Resizable: " << glfwGetWindowAttrib(win->glfwWindow, GLFW_RESIZABLE) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Decorated: " << glfwGetWindowAttrib(win->glfwWindow, GLFW_DECORATED) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Auto Iconify: " << glfwGetWindowAttrib(win->glfwWindow, GLFW_AUTO_ICONIFY) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Floating: " << glfwGetWindowAttrib(win->glfwWindow, GLFW_FLOATING) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Transparent Framebuffer: " << glfwGetWindowAttrib(win->glfwWindow, GLFW_TRANSPARENT_FRAMEBUFFER) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Focus on Show: " << glfwGetWindowAttrib(win->glfwWindow, GLFW_FOCUS_ON_SHOW) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| Context related attributes: " << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Client API: " << (glfwGetWindowAttrib(win->glfwWindow, GLFW_CLIENT_API) == GLFW_OPENGL_API ? "OpenGL API" : glfwGetWindowAttrib(win->glfwWindow, GLFW_CLIENT_API) == GLFW_OPENGL_ES_API ? "OpenGL ES API" : "No API") << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Context Creation API: " << (glfwGetWindowAttrib(win->glfwWindow, GLFW_CONTEXT_CREATION_API) == GLFW_NATIVE_CONTEXT_API ? "Native Context API" : glfwGetWindowAttrib(win->glfwWindow, GLFW_CONTEXT_CREATION_API) == GLFW_EGL_CONTEXT_API ? "EGL Context API" : "Osmesa Context API") << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Context Version: " << glfwGetWindowAttrib(win->glfwWindow, GLFW_CONTEXT_VERSION_MAJOR) << "." << glfwGetWindowAttrib(win->glfwWindow, GLFW_CONTEXT_VERSION_MINOR) << "." << glfwGetWindowAttrib(win->glfwWindow, GLFW_CONTEXT_REVISION) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| OpenGL Forward Compatibility: " << glfwGetWindowAttrib(win->glfwWindow, GLFW_OPENGL_FORWARD_COMPAT) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| OpenGL Debug Context: " << glfwGetWindowAttrib(win->glfwWindow, GLFW_OPENGL_DEBUG_CONTEXT) << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| OpenGL Profile: " << (glfwGetWindowAttrib(win->glfwWindow, GLFW_OPENGL_PROFILE) == GLFW_OPENGL_CORE_PROFILE ? "OpenGL Core Profile" : glfwGetWindowAttrib(win->glfwWindow, GLFW_OPENGL_PROFILE) == GLFW_OPENGL_COMPAT_PROFILE ? "OpenGL Compat Profile" : "OpenGL Any Profile") << std::endl;
	std::cout << "[Message][XelaWindow] ===>| ===>| Context Robustness: " << (glfwGetWindowAttrib(win->glfwWindow, GLFW_CONTEXT_ROBUSTNESS) == GLFW_LOSE_CONTEXT_ON_RESET ? "Lose Context on Reset" : glfwGetWindowAttrib(win->glfwWindow, GLFW_CONTEXT_ROBUSTNESS) == GLFW_NO_RESET_NOTIFICATION ? "No Reset Notification" : "No Robustness") << std::endl;
	std::cout << "[Message][XelaWindow] Window created with the following size: " << std::endl;
	std::cout << "[Message][XelaWindow] ===>| Framebuffer size: " << windowSizeX << ", " << windowSizeY << std::endl;
	glfwGetWindowSize(win->glfwWindow, &windowSizeX, &windowSizeY);
	std::cout << "[Message][XelaWindow] ===>| Window size: " << windowSizeX << ", " << windowSizeY << std::endl;
	#endif
	//Call second init.
	if (xelaGraphicsInitGLEW()) {
		*success = XELA_SUCCESS;
	}
	else {
		*success = XELA_ERROR_INIT_GLEW;
		#if XELA_DEBUG_WINDOW
		//Print error.
		std::cout << "[ERROR][XelaWindow] Error initializing GLEW" << std::endl;
		#endif
		return nullptr;
	}
	xelaAddWindow(win->glfwWindow, win);
	//Set clear color.
	glClearColor(win->clearColor.x, win->clearColor.y, win->clearColor.z, win->clearColor.w);
	//Enable depth testing.
	glEnable(GL_DEPTH_TEST);
	//Enable blending.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	#if XELA_DEBUG_WINDOW
	std::cout << "[Message][XelaWindow] Set " << win->winTitle << " clear color to: " << win->clearColor.x << ", " << win->clearColor.y << ", " << win->clearColor.z << ", " << win->clearColor.w << std::endl;
	#endif

	return win;
}
XelaWindow *XelaWindow::delWindow(XelaWindow *w) {
	glfwDestroyWindow(w->glfwWindow);
	return nullptr;
}

void XelaWindow::captureMouse(XelaWindow *w) {
	//Capture cursor.
	glfwSetInputMode(w->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void XelaWindow::hideMouse(XelaWindow *w) {
	//Hide cursor.
	glfwSetInputMode(w->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}
void XelaWindow::showMouse(XelaWindow *w) {
	//Show cursor.
	glfwSetInputMode(w->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
void XelaWindow::update(XelaWindow *w) {
	glfwSwapBuffers(w->glfwWindow);
	glfwPollEvents();
	xelaGraphicsProcessEvents();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void XelaWindow::setShouldClose(XelaWindow *w, bool close) {
	glfwSetWindowShouldClose(w->glfwWindow, close);
	#if XELA_DEBUG_WINDOW
	//Print new close state.
	std::cout << "[Message][XelaWindow] Updated " << w->winTitle << " should close to " << close << std::endl;
	#endif
}
void XelaWindow::setClearColor(XelaWindow *w, XelaVec4<float> rgba) {
	glClearColor(rgba.x, rgba.y, rgba.z, rgba.w);
	w->clearColor = rgba;
	#if XELA_DEBUG_WINDOW
	std::cout << "[Message][XelaWindow] Set " << w->winTitle << " clear color to: " << w->clearColor.x << ", " << w->clearColor.y << ", " << w->clearColor.z << ", " << w->clearColor.w << std::endl;
	#endif
}
void XelaWindow::setAlwaysOnTop(XelaWindow *w, bool top) {
	glfwSetWindowAttrib(w->glfwWindow, GLFW_FLOATING, top);
	#if XELA_DEBUG_WINDOW
	std::cout << "[Message][XelaWindow] Set " << w->winTitle << " Always on Top status to: " << top << std::endl;
	#endif
}
void XelaWindow::setOpacity(XelaWindow *w, float opa) {
	glfwSetWindowOpacity(w->glfwWindow, opa);
}
void XelaWindow::setSize(XelaWindow *w, int sizeX, int sizeY) {
	glfwSetWindowSize(w->glfwWindow, sizeX, sizeY);
	#if XELA_DEBUG_WINDOW
	std::cout << "[Message][XelaWindow] Set " << w->winTitle << " size to: " << sizeX << ", " << sizeY << std::endl;
	#endif
}
void XelaWindow::maximize(XelaWindow *w) {
	int windowSizeX, windowSizeY;
	glfwMaximizeWindow(w->glfwWindow);
	#if XELA_DEBUG_WINDOW
	std::cout << "[Message][XelaWindow] Maximized " << w->winTitle << std::endl;
	glfwGetFramebufferSize(w->glfwWindow, &windowSizeX, &windowSizeY);
	std::cout << "[Message][XelaWindow] New framebuffer size: " << windowSizeX << ", " << windowSizeY << std::endl;
	glfwGetWindowSize(w->glfwWindow, &windowSizeX, &windowSizeY);
	std::cout << "[Message][XelaWindow] New window size: " << windowSizeX << ", " << windowSizeY << std::endl;
	#endif
}

bool XelaWindow::shouldClose(XelaWindow *w) {
	return glfwWindowShouldClose(w->glfwWindow);
}
void XelaWindow::getSize(XelaWindow *w, int *width, int *height) {
	glfwGetWindowSize(w->glfwWindow, width, height);
}
void XelaWindow::getResolution(XelaWindow *w, int *width, int *height) {
	glfwGetFramebufferSize(w->glfwWindow, width, height);
}