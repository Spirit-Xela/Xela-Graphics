#ifndef _XELA_WINDOW_H
#define _XELA_WINDOW_H

//Libs
#include "GL/glew.h"
#include "GLFW/glfw3.h"

//Xela Graphics
#include "XelaGraphics.h"

extern "C" {
	struct XelaWindow {
		//Glfw objects.
		GLFWwindow *glfwWindow = NULL;
		GLFWmonitor *glfwMonitor = NULL;
		const GLFWvidmode *mode = NULL;
		//Window info
		const char *winTitle;
		XelaVec4<float> clearColor = { 0.0, 0.0, 0.0, 1.0 };

		//Initialize a new XelaWindow object
		//SizeX and SizeY specify the resolution of the window. If a number less than 0 is specified, sizeX/sizeY will automatically be set to the resolution of the main monitor.
		//Title specifies the title of the window to be created.
		//If fullscreen is true, the window will automatically become fullscreen on the primary monitor. Otherwise, windowed mode is used.
		//Share specifies a window to share a context with, and is nullptr by default.
		//Decorated specifies whether or not to create a decorated window.
		//Success is set to either XELA_SUCCESS, XELA_ERROR_INIT, or XELA_ERROR_WINDOW.
		//===>| XELA_SUCCESS - The window was created successfully.
		//===>| XELA_ERROR_INIT - There was an error when initializing GLEW or GLFW.
		//===>| XELA_ERROR_WINDOW - There was an error when creating the GLFWwindow object.
		XELAGRAPHICS_API static XelaWindow *genWindow(int sizeX, int sizeY, const char *title, bool fullscreen, int *success, bool decorated, XelaWindow *share = nullptr);
		XELAGRAPHICS_API static XelaWindow *delWindow(XelaWindow *w);

		//Capture the mouse on this window. Prevents the mouse from moving outside the window allowing for cursor callbacks to be used for motion-based controls.
		XELAGRAPHICS_API static void captureMouse(XelaWindow *w);
		//Hides the mouse while over this window but does not limit its movement.
		XELAGRAPHICS_API static void hideMouse(XelaWindow *w);
		//Shows the mouse and allows it to act as a normal cursor.
		XELAGRAPHICS_API static void showMouse(XelaWindow *w);
		//Update this window object. Should be called every frame.
		XELAGRAPHICS_API static void update(XelaWindow *w);
		//Set whether or not this window should close.
		XELAGRAPHICS_API static void setShouldClose(XelaWindow *w, bool close);
		//Set the clear color of the Window
		//The default before calling this function is 0, 0, 0, 1.
		XELAGRAPHICS_API static void setClearColor(XelaWindow *w, XelaVec4<float> rgba);
		//Sets whether or not this window is always on top.
		XELAGRAPHICS_API static void setAlwaysOnTop(XelaWindow *w, bool top);
		//Sets the opacity of the window.
		XELAGRAPHICS_API static void setOpacity(XelaWindow *w, float opa);
		//Sets the size of the window.
		XELAGRAPHICS_API static void setSize(XelaWindow *w, int sizeX, int sizeY);
		//Maximizes the window.
		XELAGRAPHICS_API static void maximize(XelaWindow *w);

		//Returns whether or not this window should be closed.
		//This is just another way of calling glfwWindowShouldClose().
		XELAGRAPHICS_API static bool shouldClose(XelaWindow *w);
		//Returns the size of the window.
		XELAGRAPHICS_API static void getSize(XelaWindow *w, int *width, int *height);
		//Returns the resolution of the window.
		XELAGRAPHICS_API static void getResolution(XelaWindow *w, int *width, int *height);
	};
}

#endif