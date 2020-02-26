#ifndef _XELA_WINDOW_H
#define _XELA_WINDOW_H

//Engine
#include "XelaDefinitions.h"
#include "XelaInit.h"
//Libs
#include "GLFW/glfw3.h"
//C++
#ifdef XELA_DEBUG_WINDOW
	#include <iostream>
#endif

class XelaWindow {
private:
	//Glfw objects.
	GLFWwindow *window = NULL;
	GLFWmonitor *monitor = NULL;
	const GLFWvidmode* mode = NULL;
	//Window info
	const char *winTitle;
	XelaVec4<float> clearColor = { 0.0, 0.0, 0.0, 1.0 };
public:
	//Initialize a new XelaWindow object
	//SizeX and SizeY specify the resolution of the window. If a number less than 0 is specified, sizeX/sizeY will automatically be set to the resolution of the main monitor.
	//Title specifies the title of the window to be created.
	//If fullscreen is true, the window will automatically become fullscreen on the primary monitor. Otherwise, windowed mode is used.
	//Share specifies a window to share a context with, and is nullptr by default.
	//Success is set to either XELA_SUCCESS, XELA_ERROR_INIT, or XELA_ERROR_WINDOW.
	//===>| XELA_SUCCESS - The window was created successfully.
	//===>| XELA_ERROR_INIT - There was an error when initializing GLEW or GLFW.
	//===>| XELA_ERROR_WINDOW - There was an error when creating the GLFWwindow object.
	XelaWindow(int sizeX, int sizeY, const char* title, bool fullscreen, int* success, XelaWindow* share = nullptr);
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
	XelaWindow(int sizeX, int sizeY, const char* title, bool fullscreen, int* success, bool decorated, XelaWindow *share = nullptr);
	~XelaWindow();

	//Capture the mouse on this window. Prevents the mouse from moving outside the window allowing for cursor callbacks to be used for motion-based controls.
	void captureMouse();
	//Hides the mouse while over this window but does not limit its movement.
	void hideMouse();
	//Shows the mouse and allows it to act as a normal cursor.
	void showMouse();
	//Update this window object. Should be called every frame.
	void update();
	//Set whether or not this window should close.
	void setShouldClose(bool close);
	//Set the clear color of the Window
	//The default before calling this function is 0, 0, 0, 1.
	void setClearColor(XelaVec4<float> rgba);
	//Sets whether or not this window is always on top.
	void setAlwaysOnTop(bool top);
	//Sets the opacity of the window.
	void setOpacity(float opa);
	//Sets the size of the window.
	void setSize(int sizeX, int sizeY);
	//Maximizes the window.
	void maximize();

	//Returns whether or not this window should be closed.
	//This is just another way of calling glfwWindowShouldClose().
	bool shouldClose();
	//Returns the size of the window.
	void getSize(int *width, int *height);
	//Returns the resolution of the window.
	void getResolution(int *width, int *height);
	//Returns how much time has passed since the engine was first initialized in seconds.
	//This is just another way of calling glfwGetTime().
	double getTime();
	//Returns the title of this window.
	const char *getTitle();
	//Returns the GLFWwindow object used by this XelaWindow.
	GLFWwindow *getGLFWwindow();
};

#endif