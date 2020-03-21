#ifndef _XELA_IMAGE_H
#define _XELA_IMAGE_H

//Xela Graphics
#include "XelaGraphics.h"

extern "C" {
	struct XelaImage {
		//If setImage() or setID() was used, the width, height, and numChannels in info is inaccurate.
		XelaImageInfo info = { nullptr, 0 };

		//Creates a new XelaImage struct and returns a pointer to it
		XELAGRAPHICS_API static XelaImage *genImage(const char *name, const char *path = nullptr, int *width = nullptr, int *height = nullptr, int *numChannels = nullptr, int inputFormat = -1, int textureFormat = -1);
		//Deletes a XelaImage struct
		XELAGRAPHICS_API static XelaImage *delImage(XelaImage *img);

		//Load an image from a file as this image and generate an openGL texture for it
		XELAGRAPHICS_API static void loadImage(XelaImage *img, const char *path, int *width, int *height, int *numChannels, int inputFormat, int textureFormat);
		//Set this images openGL texture id and name. Use when an openGL texture was created manually and you need to store its id here
		//Don't use this if you're using loadImage() to load images
		XELAGRAPHICS_API static void setImage(XelaImage *img, unsigned int GLid, const char *name);
		//Update the name of this image. The name of the image is the name of the uniform it gets sent to in GLSL shaders
		XELAGRAPHICS_API static void setName(XelaImage *img, const char *name);
		//Update the id of this image. Use when an openGL texture was created manually and you need to store its id here
		//Don't use this if you're using loadImage() to load images
		XELAGRAPHICS_API static void setID(XelaImage *img, unsigned int GLid);
	};
}

#endif