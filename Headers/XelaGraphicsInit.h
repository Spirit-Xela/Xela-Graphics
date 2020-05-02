#ifndef _XELA_INIT_H
#define _XELA_INIT_H

//Xela Graphics
#include "XelaGraphics.h"

extern "C" {
	//Initializes the Xela Graphics library.
	XELAGRAPHICS_API bool xelaGraphicsInit();
	//Initializes GLEW, which needs to be done seperately from XelaInit().
	XELAGRAPHICS_API bool xelaGraphicsInitGLEW();
	//Unloads the Xela Graphics library.
	XELAGRAPHICS_API bool xelaGraphicsTerminate();
}

#endif