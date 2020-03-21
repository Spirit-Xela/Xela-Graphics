/*=====================================================================
Xela Graphics
Created by: Alex Morse
Version 1.2.0 - 03/19/2020

A simple graphics library meant to make is easier to get started using OpenGL while also adding some functionality not originally present in glfw and glew.

Libraries used:
GLFW 3.3
GLEW 2.1.0
FreeType 2.10.1
stb_image.h
=====================================================================*/
#ifndef _XELA_GRAPHICS_H
#define _XELA_GRAPHICS_H

#include <vector>

#define XELA_GRAPHICS_VERSION_MAJOR 1
#define XELA_GRAPHICS_VERSION_MINOR 1
#define XELA_GRAPHICS_VERSION_REVISION 0

//Export definitions
#if defined(_WIN32) or defined(_WIN64)
	#if defined(XELAGRAPHICS_EXPORTS)
		#define XELAGRAPHICS_API __declspec(dllexport)
	#else
		#define XELAGRAPHICS_API __declspec(dllimport)
	#endif
#else
	#define XELAGRAPHICS_API
#endif

//Utility functions
//=====================================================================
//Returns how much time has passed since the engine was first initialized in seconds.
//This is just another way of calling glfwGetTime().
extern "C" {
	XELAGRAPHICS_API double xelaGetTime();
}
//=====================================================================

//Structures
//=====================================================================
//Structures to store coordinates
template<typename T>
struct XelaVec2 {
	T x, y;
};
template<typename T>
struct XelaVec3 {
	T x, y, z;
};
template<typename T>
struct XelaVec4 {
	T x, y, z, w;
};
//Strcture to store vertex information. Used in XelaObject to keep track of data meant to go to different locations in shaders.
template<typename T>
struct XelaVertexData {
	int id;
	int dataSize;
	int update;
	std::vector<T> data;
};
//=====================================================================

//Debug
//=====================================================================
#define XELA_DEBUG_CALLBACKS 0
#define XELA_DEBUG_EVENTS 0
#define XELA_DEBUG_INIT 1
#define XELA_DEBUG_WINDOW 1
#define XELA_DEBUG_SHADER 1
#define XELA_DEBUG_FONT 1
//=====================================================================

//Shaders
//=====================================================================
typedef void(*ShaderCallbackFunction)(unsigned int program);
//Stores info for texture to pass to shader
struct XelaImageInfo {
	const char *name;
	unsigned int id;
	int width;
	int height;
	int numChannels;
};
//Store uniform info for shaders
struct XelaUniformInfo {
	const char *name;
	int size;
	int inFormat, outFormat;
	void *data;
};
//Define data types
#define XELA_BOOL 0
#define XELA_INT 1
#define XELA_UNSIGNED_INT 2
#define XELA_FLOAT 3
#define XELA_DOUBLE 4
//Redefining GL things with XELA prefix
#define XELA_R GL_R
#define XELA_RG GL_RG
#define XELA_RGB GL_RGB
#define XELA_RGBA GL_RGBA
#define XELA_SRGB GL_SRGB
#define XELA_SRGBA GL_SRGB_ALPHA
//=====================================================================

//Init
//=====================================================================
//OpenGL version
#define XELA_GLFW_MAJOR 3
#define XELA_GLFW_MINOR 3
//Is the window resizable
#define XELA_RESIZABLE GLFW_TRUE
#define XELA_DOUBLE_BUFFERED GLFW_TRUE
#define XELA_FORWARD_COMPAT GLFW_TRUE
#define XELA_PROFILE GLFW_OPENGL_CORE_PROFILE
#define XELA_TRANSPARENT_FRAMEBUFFER GL_TRUE
//=====================================================================

//Errors
//=====================================================================
#define XELA_ERROR_UNKNOWN 0
#define XELA_SUCCESS 1
#define XELA_ERROR_INIT 2
#define XELA_ERROR_WINDOW 3
#define XELA_ERROR_INIT_GLEW 4
#define XELA_ERROR_FREETYPE_INIT 5
#define XELA_ERROR_FREETYPE_LOAD_CHAR 6
#define XELA_ERROR_UNKNOWN_FORMAT 7
//=====================================================================

//Keys - just redefining things defined by glfw.
//This is mostly for consistency in using the xela prefix for programs that use Xela Graphics, but also shortens some definitions.
//For example, GLFW_KEY_COMMA was defined as XELA_COMMA since I saw no reason to explicitly state that it was the comma key.
//1) OpenGL defined comma as the ascii value for the comma character anyway.
//2) I couldn't think of a situation in which a distinction between comma and the comma key was necessary.
//=====================================================================
#define XELA_PRESS GLFW_PRESS
#define XELA_RELEASE GLFW_RELEASE
//=====================================================================
#define XELA_MOUSE_LEFT GLFW_MOUSE_BUTTON_LEFT
#define XELA_MOUSE_RIGHT GLFW_MOUSE_BUTTON_RIGHT
#define XELA_MOUSE_MIDDLE GLFW_MOUSE_BUTTON_MIDDLE
#define XELA_MOUSE_LAST GLFW_MOUSE_BUTTON_LAST
#define XELA_MOUSE_1 GLFW_MOUSE_BUTTON_1
#define XELA_MOUSE_2 GLFW_MOUSE_BUTTON_2
#define XELA_MOUSE_3 GLFW_MOUSE_BUTTON_3
#define XELA_MOUSE_4 GLFW_MOUSE_BUTTON_4
#define XELA_MOUSE_5 GLFW_MOUSE_BUTTON_5
#define XELA_MOUSE_6 GLFW_MOUSE_BUTTON_6
#define XELA_MOUSE_7 GLFW_MOUSE_BUTTON_7
#define XELA_MOUSE_8 GLFW_MOUSE_BUTTON_8
//=====================================================================
#define XELA_UNKNOWN GLFW_KEY_UNKNOWN
#define XELA_SPACE GLFW_KEY_SPACE /*   */
#define XELA_APOSTROPHE GLFW_KEY_APOSTROPHE /* ' */
#define XELA_COMMA GLFW_KEY_COMMA/* , */
#define XELA_MINUS GLFW_KEY_MINUS /* - */
#define XELA_PERIOD GLFW_KEY_PERIOD /* . */
#define XELA_SLASH GLFW_KEY_SLASH /* / */
#define XELA_0 GLFW_KEY_0 /* 0 */
#define XELA_1 GLFW_KEY_1 /* 1 */
#define XELA_2 GLFW_KEY_2 /* 2 */
#define XELA_3 GLFW_KEY_3 /* 3 */
#define XELA_4 GLFW_KEY_4 /* 4 */
#define XELA_5 GLFW_KEY_5 /* 5 */
#define XELA_6 GLFW_KEY_6 /* 6 */
#define XELA_7 GLFW_KEY_7 /* 7 */
#define XELA_8 GLFW_KEY_8 /* 8 */
#define XELA_9 GLFW_KEY_9 /* 8 */
#define XELA_SEMICOLON GLFW_KEY_SEMICOLON /* ; */
#define XELA_EQUAL GLFW_KEY_EQUAL /* = */
#define XELA_A GLFW_KEY_A /* A */
#define XELA_B GLFW_KEY_B /* B */
#define XELA_C GLFW_KEY_C /* C */
#define XELA_D GLFW_KEY_D /* D */
#define XELA_E GLFW_KEY_E /* E */
#define XELA_F GLFW_KEY_F /* F */
#define XELA_G GLFW_KEY_G /* G */
#define XELA_H GLFW_KEY_H /* H */
#define XELA_I GLFW_KEY_I /* I */
#define XELA_J GLFW_KEY_J /* J */
#define XELA_K GLFW_KEY_K /* K */
#define XELA_L GLFW_KEY_L /* L */
#define XELA_M GLFW_KEY_M /* M */
#define XELA_N GLFW_KEY_N /* N */
#define XELA_O GLFW_KEY_O /* O */
#define XELA_P GLFW_KEY_P /* P */
#define XELA_Q GLFW_KEY_Q /* Q */
#define XELA_R GLFW_KEY_R /* R */
#define XELA_S GLFW_KEY_S /* S */
#define XELA_T GLFW_KEY_T /* T */
#define XELA_U GLFW_KEY_U /* U */
#define XELA_V GLFW_KEY_V /* V */
#define XELA_W GLFW_KEY_W /* W */
#define XELA_X GLFW_KEY_X /* X */
#define XELA_Y GLFW_KEY_Y /* Y */
#define XELA_Z GLFW_KEY_Z /* Z */
#define XELA_LEFT_BRACKET GLFW_KEY_LEFT_BRACKET /* [ */
#define XELA_BACKSLASH GLFW_KEY_BACKSLASH /* \ */
#define XELA_RIGHT_BRACKET GLFW_KEY_RIGHT_BRACKET /* ] */
#define XELA_GRAVE GLFW_KEY_GRAVE_ACCENT /* ` */
#define XELA_WORLD_1 GLFW_KEY_WORLD_1 /* non-US #1 */
#define XELA_WORLD_2 GLFW_KEY_WORLD_2 /* non-US #2 */
#define XELA_ESCAPE GLFW_KEY_ESCAPE /* Escape */
#define XELA_ENTER GLFW_KEY_ENTER /* Enter */
#define XELA_TAB GLFW_KEY_TAB /* Tab */
#define XELA_BACKSPACE GLFW_KEY_BACKSPACE /* Backspace */
#define XELA_INSERT GLFW_KEY_INSERT /* Insert */
#define XELA_DELETE GLFW_KEY_DELETE /* Delete */
#define XELA_RIGHT GLFW_KEY_RIGHT /* Right Arrow */
#define XELA_LEFT GLFW_KEY_LEFT /* Left Arrow */
#define XELA_DOWN GLFW_KEY_DOWN /* Down Arrow */
#define XELA_UP GLFW_KEY_UP /* Up Arrow */
#define XELA_PAGE_UP GLFW_KEY_PAGE_UP /* Page Up */
#define XELA_PAGE_DOWN GLFW_KEY_PAGE_DOWN /* Page Down */
#define XELA_HOME GLFW_KEY_HOME /* Home */
#define XELA_END GLFW_KEY_END /* End */
#define XELA_CAPS_LOCK GLFW_KEY_CAPS_LOCK /* Caps Lock */
#define XELA_SCROLL_LOCK GLFW_KEY_SCROLL_LOCK /* Scroll Lock */
#define XELA_NUM_LOCK GLFW_KEY_NUM_LOCK /* Num Lock */
#define XELA_PRINT_SCREEN GLFW_KEY_PRINT_SCREEN /* Print Screen */
#define XELA_PAUSE GLFW_KEY_PAUSE /* Pause */
#define XELA_F1 GLFW_KEY_F1 /* F1 */
#define XELA_F2 GLFW_KEY_F2 /* F2 */
#define XELA_F3 GLFW_KEY_F3 /* F3 */
#define XELA_F4 GLFW_KEY_F4 /* F4 */
#define XELA_F5 GLFW_KEY_F5 /* F5 */
#define XELA_F6 GLFW_KEY_F6 /* F6 */
#define XELA_F7 GLFW_KEY_F7 /* F7 */
#define XELA_F8 GLFW_KEY_F8 /* F8 */
#define XELA_F9 GLFW_KEY_F9 /* F9 */
#define XELA_F10 GLFW_KEY_F10 /* F10 */
#define XELA_F11 GLFW_KEY_F11 /* F11 */
#define XELA_F12 GLFW_KEY_F12 /* F12 */
#define XELA_F13 GLFW_KEY_F13 /* F13 */
#define XELA_F14 GLFW_KEY_F14 /* F14 */
#define XELA_F15 GLFW_KEY_F15 /* F15 */
#define XELA_F16 GLFW_KEY_F16 /* F16 */
#define XELA_F17 GLFW_KEY_F17 /* F17 */
#define XELA_F18 GLFW_KEY_F18 /* F18 */
#define XELA_F19 GLFW_KEY_F19 /* F19 */
#define XELA_F20 GLFW_KEY_F20 /* F20 */
#define XELA_F21 GLFW_KEY_F21 /* F21 */
#define XELA_F22 GLFW_KEY_F22 /* F22 */
#define XELA_F23 GLFW_KEY_F23 /* F23 */
#define XELA_F24 GLFW_KEY_F24 /* F24 */
#define XELA_F25 GLFW_KEY_F25 /* F25 */
#define XELA_NUMPAD_0 GLFW_KEY_KP_0 /* Numpad 0 */
#define XELA_NUMPAD_1 GLFW_KEY_KP_1 /* Numpad 1 */
#define XELA_NUMPAD_2 GLFW_KEY_KP_2 /* Numpad 2 */
#define XELA_NUMPAD_3 GLFW_KEY_KP_3 /* Numpad 3 */
#define XELA_NUMPAD_4 GLFW_KEY_KP_4 /* Numpad 4 */
#define XELA_NUMPAD_5 GLFW_KEY_KP_5 /* Numpad 5 */
#define XELA_NUMPAD_6 GLFW_KEY_KP_6 /* Numpad 6 */
#define XELA_NUMPAD_7 GLFW_KEY_KP_7 /* Numpad 7 */
#define XELA_NUMPAD_8 GLFW_KEY_KP_8 /* Numpad 8 */
#define XELA_NUMPAD_9 GLFW_KEY_KP_9 /* Numpad 9 */
#define XELA_NUMPAD_DECIMAL GLFW_KEY_KP_DECIMAL /* Numpad . */
#define XELA_NUMPAD_DIVIDE GLFW_KEY_KP_DIVIDE /* Numpad / */
#define XELA_NUMPAD_MULTIPLY GLFW_KEY_KP_MULTIPLY /* Numpad * */
#define XELA_NUMPAD_SUBTRACT GLFW_KEY_KP_SUBTRACT /* Numpad - */
#define XELA_NUMPAD_ADD GLFW_KEY_KP_ADD /* Numpad + */
#define XELA_NUMPAD_ENTER GLFW_KEY_KP_ENTER /* Numpad Enter */
#define XELA_NUMPAD_EQUAL GLFW_KEY_KP_EQUAL /* Numpad + */
#define XELA_LEFT_SHIFT GLFW_KEY_LEFT_SHIFT /* Left Shift */
#define XELA_LEFT_CONTROL GLFW_KEY_LEFT_CONTROL /* Left Control */
#define XELA_LEFT_ALT GLFW_KEY_LEFT_ALT /* Left Alt */
#define XELA_LEFT_SUPER GLFW_KEY_LEFT_SUPER /* Left Super */
#define XELA_RIGHT_SHIFT GLFW_KEY_RIGHT_SHIFT /* Right Shift */
#define XELA_RIGHT_CONTROL GLFW_KEY_RIGHT_CONTROL /* Right Control */
#define XELA_RIGHT_ALT GLFW_KEY_RIGHT_ALT /* Right Alt */
#define XELA_RIGHT_SUPER GLFW_KEY_RIGHT_SUPER /* Right Super */
#define XELA_MENU GLFW_KEY_MENU /* Right Menu */
#define XELA_LAST GLFW_KEY_LAST /* GLFW_KEY_MENU */
//=====================================================================

#endif