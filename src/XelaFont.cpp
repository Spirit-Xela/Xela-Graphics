#include "XelaFont.h"

bool ftInit = false;

int freetypeSetup(FT_Library *library) {
	if (!ftInit) {
		FT_Error error = FT_Init_FreeType(library);
		if (error) {
#ifdef XELA_DEBUG_FONT
			std::cout << "[ERROR][XelaFont] Unknown error occurred while initializing freetype" << std::endl;
#endif
			return XELA_ERROR_FREETYPE_INIT;
		};

		ftInit = true;
	}

	return XELA_SUCCESS;
}
int createFace(FT_Library *library, FT_Face *face, std::string ttf) {
	FT_Error error = FT_New_Face(*library, ttf.c_str(), 0, face);
	if (error == FT_Err_Unknown_File_Format) {
#ifdef XELA_DEBUG_FONT
		std::cout << "[ERROR][XelaFont] Unknown file format for font file: " << ttf << std::endl;
#endif
		return XELA_ERROR_UNKNOWN_FORMAT;
	}
	else if (error) {
#ifdef XELA_DEBUG_FONT
		std::cout << "[ERROR][XelaFont] Unknown error occured while loading font file: " << ttf << std::endl;
#endif
		return XELA_ERROR_UNKNOWN;
	}

	return XELA_SUCCESS;
}
int setFontSize(FT_Face *face, int width, int height) {
	FT_Error error = FT_Set_Pixel_Sizes(*face, width, height);
	if (error) {
#ifdef XELA_DEBUG_FONT
		std::cout << "[ERROR][XelaFont] Unknown error occurred while setting font size" << std::endl;
#endif
		return XELA_ERROR_UNKNOWN;
	}

	return XELA_SUCCESS;
}

XelaFont::XelaFont() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void XelaFont::clearFont() {
	fontTexture.clear();
	glyphs.clear();
}

int XelaFont::loadGlyph(char g) {
	error = FT_Load_Char(face, (unsigned int)g, FT_LOAD_RENDER);
	if (error) {
#ifdef XELA_DEBUG_FONT
		std::cout << "[ERROR][XelaFont] Error loading character: " << g << std::endl;
#endif
		return XELA_ERROR_FREETYPE_LOAD_CHAR;
	}

	if (fontTexture.size() == 0) {
		for (int i = 0; i <= face->glyph->bitmap.width * face->glyph->bitmap.rows; i++) {
			fontTexture.push_back(face->glyph->bitmap.buffer[i]);
		}
		texWidth = face->glyph->bitmap.width;
		texHeight = face->glyph->bitmap.rows;

		XelaGlyph glyph;
		glyph.glyph = g;
		glyph.up = 0;
		glyph.left = 0;
		glyph.down = texHeight;
		glyph.right = texWidth;
		glyph.width = texWidth;
		glyph.height = texHeight;
		glyph.bearingX = face->glyph->bitmap_left;
		glyph.bearingY = face->glyph->bitmap_top;
		glyph.advance = (face->glyph->metrics.horiAdvance / 64) + glyph.bearingX;

		glyphs.emplace(g, glyph);
	}
	else {
		int width = face->glyph->bitmap.width + 2;
		int height = face->glyph->bitmap.rows;
		int startX = texWidth;

		std::vector<unsigned char> grab;
		for (int i = 0; i < face->glyph->bitmap.width * face->glyph->bitmap.rows; i++) {
			if (i % face->glyph->bitmap.width == 0) {
				//Add zeroes to side to pad texture
				//This is so that if you scale the texture up or down while rendering, the GL_NEAREST scaling option doesn't take values from nearby glyphs
				grab.push_back(0);
				grab.push_back(0);
			}
			grab.push_back(face->glyph->bitmap.buffer[i]);
		}

		for (int x = 0; x < width; x++) {
			texWidth++;
			for (int y = 0; y < height && y < texHeight; y++) {
				int insertIndex = (texWidth - 1) + (texWidth * y);
				int grabIndex = (width * y) + x;

				if (insertIndex >= fontTexture.size()) {
					fontTexture.push_back(grab[grabIndex]);
				}
				else {
					fontTexture.insert(fontTexture.begin() + insertIndex, grab[grabIndex]);
				}
			}
		}
		for (int y = height; y < texHeight; y++) {
			int w = (texWidth - width);
			int insertIndex = w + (w * y) + (width * y);
			for (int x = 0; x < width; x++) {
  				fontTexture.insert(fontTexture.begin() + insertIndex, 0);
			}
		}
		for (int y = texHeight; y < height; y++) {
			for (int x = 0; x < texWidth; x++) {
				int currX = x - startX;
				if (currX < 0) {
					fontTexture.push_back(0);
				}
				else {
					int grabIndex = (width * y) + currX;
					fontTexture.push_back(grab[grabIndex]);
				}
			}
		}
		if (height > texHeight) {
			texHeight = height;
		}

		XelaGlyph glyph;
		glyph.glyph = g;
		glyph.up = 0;
		glyph.left = startX + 2;
		glyph.down = height;
		glyph.right = startX + width;
		glyph.width = width;
		glyph.height = height;
		glyph.bearingX = face->glyph->bitmap_left;
		glyph.bearingY = face->glyph->bitmap_top;
		glyph.advance = (face->glyph->metrics.horiAdvance / 64) + glyph.bearingX;
		
		glyphs.emplace(g, glyph);
	}

	return XELA_SUCCESS;
}
void XelaFont::genTexture() {
	glDeleteTextures(1, &info.id);
	//Generate texture
	glGenTextures(1, &info.id);
	glBindTexture(GL_TEXTURE_2D, info.id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, texWidth, texHeight, 0, GL_RED, GL_UNSIGNED_BYTE, fontTexture.data());
	//Set texture options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Store info
	info.width = texWidth;
	info.height = texHeight;
}

int XelaFont::loadFont(std::string ttf, int size) {
	clearFont();

	int suc = freetypeSetup(&library);
	if (suc != XELA_SUCCESS)
		return suc;

	suc = createFace(&library, &face, ttf);
	if (suc != XELA_SUCCESS)
		return suc;

	suc = setFontSize(&face, size, size);
	if (suc != XELA_SUCCESS)
		return suc;

	fontName = face->family_name;

	return XELA_SUCCESS;
}
XelaGlyph XelaFont::getGlyph(char g, int *success) {
	*success = XELA_SUCCESS;

	std::unordered_map<char, XelaGlyph>::iterator it = glyphs.find(g);
	if (it == glyphs.end()) {
		*success = loadGlyph(g);

		if (*success == XELA_ERROR_FREETYPE_INIT) {
#ifdef XELA_DEBUG_FONT
			std::cout << "[ERROR][XELAFONT] Error initializing freetype while loading character: " << g << std::endl;
#endif
		}
		else if (*success == XELA_ERROR_FREETYPE_LOAD_CHAR) {
#ifdef XELA_DEBUG_FONT
			std::cout << "[ERROR][XELAFONT] Error loading character: " << g << std::endl;
#endif
		}
	}

	return glyphs.at(g);
}
XelaFontTextureInfo XelaFont::getTexInfo() {
	return info;
}