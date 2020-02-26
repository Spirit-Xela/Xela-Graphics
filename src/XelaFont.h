#ifndef _XELA_FONT_H
#define _XELA_FONT_H

//Engine
#include "XelaDefinitions.h"
//Libs
#include <ft2build.h>
#include FT_FREETYPE_H
#include "GL/glew.h"
#include "GLFW/glfw3.h"
//C++
#ifdef XELA_DEBUG_FONT
	#include <iostream>
#endif
#include <string>
#include <unordered_map>
#include <vector>

//Information about a single glyph in a font.
struct XelaGlyph {
	char glyph = 0;
	int up, left, down, right;
	int width, height;
	int bearingX, bearingY;
	int advance;
};
//Information about a font's texture.
struct XelaFontTextureInfo {
	GLuint id;
	int width, height;
};

class XelaFont {
private:
	//Texture data.
	std::vector<unsigned char> fontTexture;
	XelaFontTextureInfo info = { 0, 0, 0 };
	int texWidth = 0, texHeight = 0;

	//Font info.
	std::string fontName = "";

	//Glyph data.
	std::unordered_map<char, XelaGlyph> glyphs;

	//Freetype variables.
	FT_Library library = nullptr;
	FT_Face face = nullptr;
	FT_Error error;

	//Clears the font's texture.
	void clearFont();

	//Loads a new glyph into the texture.
	int loadGlyph(char g);
public:
	XelaFont();

	//Load a new font file. Replaces any font file previously loaded by this instance of XelaFont.
	//Returns an integer representing whether or not this function was successful.
	//===>| XELA_SUCCESS - Font loaded successfully.
	//===>| XELA_ERROR_UNKNOWN - Unknown error occurred.
	//===>| XELA_ERROR_FREETYPE_INIT - Unable to initialize the freetype library.
	//===>| XELA_ERROR_UNKNOWN_FORMAT - Font file provided was not recognized as a font file.
	int loadFont(std::string ttf, int size);
	//Generates a new OpenGL texture for this font.
	void genTexture();

	//Returns a XelaGlyph struct for the specified character.
	//If the specified character has not yet been loaded into the font, it is automatically loaded then returned.
	//Success is set depending on whether this function was successful.
	//===>| XELA_SUCCESS - Glyph loaded successfully.
	//===>| XELA_ERROR_FREETYPE_LOAD_CHAR - Error occurred while loading the character glyph.
	XelaGlyph getGlyph(char g, int *success);

	//Returns the texture information for this font.
	XelaFontTextureInfo getTexInfo();
};

#endif