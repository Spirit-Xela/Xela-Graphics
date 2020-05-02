//Libs
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

//Xela Graphics
#include "XelaImage.h"

XelaImage *XelaImage::genImage(const char *name, const char *path, int *width, int *height, int *numChannels, int inputFormat, int textureFormat) {
	XelaImage *img = new XelaImage;
	img->info.name = name;
	if (path != nullptr) {
		XelaImage::loadImage(img, path, width, height, numChannels, inputFormat, textureFormat);
	}
	return img;
}
XelaImage *XelaImage::delImage(XelaImage *img) {
	delete img;
	return nullptr;
}

void XelaImage::loadImage(XelaImage *img, const char *path, int *width, int *height, int *numChannels, int inputFormat, int textureFormat) {
	//Load data with stb_image
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(path, width, height, numChannels, 0);

	//Generate OpenGL texture.
	glDeleteTextures(1, &img->info.id);
	glGenTextures(1, &img->info.id);
	glBindTexture(GL_TEXTURE_2D, img->info.id);
	glTexImage2D(GL_TEXTURE_2D, 0, inputFormat, *width, *height, 0, textureFormat, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	//Free data.
	stbi_image_free(data);

	img->info.width = *width;
	img->info.height = *height;
	img->info.numChannels = *numChannels;
}
void XelaImage::setImage(XelaImage *img, unsigned int GLid, const char *name) {
	img->info.name = name;
	img->info.id = GLid;
}
void XelaImage::setName(XelaImage *img, const char *name) {
	img->info.name = name;
}
void XelaImage::setID(XelaImage *img, unsigned int GLid) {
	img->info.id = GLid;
}