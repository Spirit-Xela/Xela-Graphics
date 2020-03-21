//Xela Graphics
#include "XelaFont.h"

//C++
#if XELA_DEBUG_FONT
#include <iostream>
#endif

static bool xelagraphics_ftInit = false;

int xelaFreetypeSetup(FT_Library *library) {
	if (!xelagraphics_ftInit) {
		FT_Error error = FT_Init_FreeType(library);
		if (error) {
			#if XELA_DEBUG_FONT
			std::cout << "[ERROR][XelaFont] Unknown error occurred while initializing freetype" << std::endl;
			#endif
			return XELA_ERROR_FREETYPE_INIT;
		};

		xelagraphics_ftInit = true;
	}

	return XELA_SUCCESS;
}
int xelaCreateFace(FT_Library *library, FT_Face *face, std::string ttf) {
	FT_Error error = FT_New_Face(*library, ttf.c_str(), 0, face);
	if (error == FT_Err_Unknown_File_Format) {
		#if XELA_DEBUG_FONT
		std::cout << "[ERROR][XelaFont] Unknown file format for font file: " << ttf << std::endl;
		#endif
		return XELA_ERROR_UNKNOWN_FORMAT;
	}
	else if (error) {
		#if XELA_DEBUG_FONT
		std::cout << "[ERROR][XelaFont] Unknown error occured while loading font file: " << ttf << std::endl;
		#endif
		return XELA_ERROR_UNKNOWN;
	}

	return XELA_SUCCESS;
}
int xelaSetFontSize(FT_Face *face, int width, int height) {
	FT_Error error = FT_Set_Pixel_Sizes(*face, width, height);
	if (error) {
		#if XELA_DEBUG_FONT
		std::cout << "[ERROR][XelaFont] Unknown error occurred while setting font size" << std::endl;
		#endif
		return XELA_ERROR_UNKNOWN;
	}

	return XELA_SUCCESS;
}

static void xelaClearFont(XelaFont *f) {
	f->fontTexture.clear();
	f->glyphs.clear();
}

int xelaLoadFontGlyph(XelaFont *f, char g) {
	f->error = FT_Load_Char(f->face, (unsigned int)g, FT_LOAD_RENDER);
	if (f->error) {
		#if XELA_DEBUG_FONT
		std::cout << "[ERROR][XelaFont] Error loading character: " << g << std::endl;
		#endif
		return XELA_ERROR_FREETYPE_LOAD_CHAR;
	}

	if (f->fontTexture.size() == 0) {
		for (int i = 0; i <= f->face->glyph->bitmap.width * f->face->glyph->bitmap.rows; i++) {
			f->fontTexture.push_back(f->face->glyph->bitmap.buffer[i]);
		}
		f->texWidth = f->face->glyph->bitmap.width;
		f->texHeight = f->face->glyph->bitmap.rows;

		XelaGlyph glyph;
		glyph.glyph = g;
		glyph.up = 0;
		glyph.left = 0;
		glyph.down = f->texHeight;
		glyph.right = f->texWidth;
		glyph.width = f->texWidth;
		glyph.height = f->texHeight;
		glyph.bearingX = f->face->glyph->bitmap_left;
		glyph.bearingY = f->face->glyph->bitmap_top;
		glyph.advance = (f->face->glyph->metrics.horiAdvance / 64) + glyph.bearingX;

		f->glyphs.emplace(g, glyph);
	}
	else {
		int width = f->face->glyph->bitmap.width + 2;
		int height = f->face->glyph->bitmap.rows;
		int startX = f->texWidth;

		std::vector<unsigned char> grab;
		for (int i = 0; i < f->face->glyph->bitmap.width * f->face->glyph->bitmap.rows; i++) {
			if (i % f->face->glyph->bitmap.width == 0) {
				//Add zeroes to side to pad texture
				//This is so that if you scale the texture up or down while rendering, the GL_NEAREST scaling option doesn't take values from nearby glyphs
				grab.push_back(0);
				grab.push_back(0);
			}
			grab.push_back(f->face->glyph->bitmap.buffer[i]);
		}

		for (int x = 0; x < width; x++) {
			f->texWidth++;
			for (int y = 0; y < height && y < f->texHeight; y++) {
				int insertIndex = (f->texWidth - 1) + (f->texWidth * y);
				int grabIndex = (width * y) + x;

				if (insertIndex >= f->fontTexture.size()) {
					f->fontTexture.push_back(grab[grabIndex]);
				}
				else {
					f->fontTexture.insert(f->fontTexture.begin() + insertIndex, grab[grabIndex]);
				}
			}
		}
		for (int y = height; y < f->texHeight; y++) {
			int w = (f->texWidth - width);
			int insertIndex = w + (w * y) + (width * y);
			for (int x = 0; x < width; x++) {
				f->fontTexture.insert(f->fontTexture.begin() + insertIndex, 0);
			}
		}
		for (int y = f->texHeight; y < height; y++) {
			for (int x = 0; x < f->texWidth; x++) {
				int currX = x - startX;
				if (currX < 0) {
					f->fontTexture.push_back(0);
				}
				else {
					int grabIndex = (width * y) + currX;
					f->fontTexture.push_back(grab[grabIndex]);
				}
			}
		}
		if (height > f->texHeight) {
			f->texHeight = height;
		}

		XelaGlyph glyph;
		glyph.glyph = g;
		glyph.up = 0;
		glyph.left = startX + 2;
		glyph.down = height;
		glyph.right = startX + width;
		glyph.width = width;
		glyph.height = height;
		glyph.bearingX = f->face->glyph->bitmap_left;
		glyph.bearingY = f->face->glyph->bitmap_top;
		glyph.advance = (f->face->glyph->metrics.horiAdvance / 64) + glyph.bearingX;

		f->glyphs.emplace(g, glyph);
	}

	return XELA_SUCCESS;
}

XelaFont *XelaFont::genFont() {
	XelaFont *font = new XelaFont();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return font;
}

void XelaFont::genTexture(XelaFont *f) {
	glDeleteTextures(1, &f->info.id);
	//Generate texture
	glGenTextures(1, &f->info.id);
	glBindTexture(GL_TEXTURE_2D, f->info.id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, f->texWidth, f->texHeight, 0, GL_RED, GL_UNSIGNED_BYTE, f->fontTexture.data());
	//Set texture options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Store info
	f->info.width = f->texWidth;
	f->info.height = f->texHeight;
}

int XelaFont::loadFont(XelaFont *f, const char *ttf, int size) {
	xelaClearFont(f);

	int suc = xelaFreetypeSetup(&f->library);
	if (suc != XELA_SUCCESS)
		return suc;

	suc = xelaCreateFace(&f->library, &f->face, ttf);
	if (suc != XELA_SUCCESS)
		return suc;

	suc = xelaSetFontSize(&f->face, size, size);
	if (suc != XELA_SUCCESS)
		return suc;

	f->fontName = f->face->family_name;

	return XELA_SUCCESS;
}
XelaGlyph XelaFont::getGlyph(XelaFont *f, char g, int *success) {
	*success = XELA_SUCCESS;

	std::unordered_map<char, XelaGlyph>::iterator it = f->glyphs.find(g);
	if (it == f->glyphs.end()) {
		*success = xelaLoadFontGlyph(f, g);

		if (*success == XELA_ERROR_FREETYPE_INIT) {
			#if XELA_DEBUG_FONT
			std::cout << "[ERROR][XELAFONT] Error initializing freetype while loading character: " << g << std::endl;
			#endif
		}
		else if (*success == XELA_ERROR_FREETYPE_LOAD_CHAR) {
			#if XELA_DEBUG_FONT
			std::cout << "[ERROR][XELAFONT] Error loading character: " << g << std::endl;
			#endif
		}
	}

	return f->glyphs.at(g);
}