#ifndef _XELA_CALLBACKS_H
#define _XELA_CALLBACKS_H

//OpenGL
#include "GL/glew.h"
#include "GLFW/glfw3.h"

//Initialize callback functions
void xelaGraphicsInitCallbacks(GLFWwindow *window);
//Handle key presses
void xelaKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
//Handle mouse events
void xelaMouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
//Handle mouse movement
void xelaCursorPosCallback(GLFWwindow *window, double xpos, double ypos);
//Handle window resizing
void xelaWindowSizeCallback(GLFWwindow *window, int width, int height);


#endif