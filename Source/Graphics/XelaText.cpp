//Xela Graphics
#include "XelaText.h"
#include "XelaShader.h"

//C++
#include <vector>

//Vertex shader for text.
std::string XelaText_vSrc =
"#version 330 core\n"
"layout (location = 0) in vec2 vert;\n"
"layout (location = 1) in vec2 tex;\n"

"uniform vec2 resolution;\n"
"uniform vec3 position;\n"
"uniform vec2 scale;\n"

"out vec2 texCoord;\n"

"void main() {\n"
//Scale object then add position.
"   vec2 pos = vec2(vert.x * scale.x, vert.y * scale.y) + position.xy;\n"
//Scale based on resolution.
"   pos = pos.xy / resolution.xy;\n"
//Move (0, 0) to bottom left and (resolution.x, resolution.y) to top right.
"   pos = (pos.xy * 2) - vec2(1, 1);\n"
"   gl_Position = vec4(pos.xy, position.z, 1);\n"
"   texCoord = tex;"
"}";

//Fragment shader for text.
std::string XelaText_fSrc =
"#version 330 core\n"

"out vec4 color;\n"
"in vec2 texCoord;\n"

"uniform sampler2D text;\n"
"uniform ivec2 textSize;\n"
"uniform vec4 textColor;\n"

"void main() {\n"
"   float sample = texture(text, texCoord.xy / textSize.xy).r;\n"
"   if (sample <= 0.01) {\n"
"       discard;\n"
"   }\n"
"   color = textColor;\n"
"}";

XelaShader *XelaText_shader = nullptr;

XelaText *XelaText::genText(XelaFont *f) {
	if (XelaText_shader == nullptr) {
		XelaText_shader = XelaShader::genShader(XelaText_vSrc.c_str(), nullptr, XelaText_fSrc.c_str());
	}

	XelaText *text = new XelaText();
	text->font = f;
	return text;
}

static void xelaGenTextObject(XelaText *t) {
	//Create new XelaObject.
	if (t->object != nullptr) {
		delete t->object;
	}
	t->object = XelaObject::genObject();

	//Load all glyphs for the text.
	std::vector<XelaGlyph> glyphs;
	int suc = 0;
	for (int i = 0; i < t->text.length(); i++) {
		glyphs.push_back(t->font->getGlyph(t->font, t->text[i], &suc));
	}
	//Generate font texture.
	t->font->genTexture(t->font);

	//Object data
	int x = 0;
	std::vector<XelaVec2<float>> verts;
	std::vector<XelaVec2<float>> texs;
	std::vector<XelaVec3<unsigned int>> inds;
	XelaFontTextureInfo info = t->font->info;

	unsigned int ind = 0;
	for (int i = 0; i < glyphs.size(); i++) {
		if (glyphs[i].glyph != ' ') {
			//Vertices
			verts.push_back({ (float)x + glyphs[i].bearingX                  , (float)glyphs[i].bearingY - glyphs[i].height });
			verts.push_back({ (float)x + glyphs[i].bearingX + glyphs[i].width, (float)glyphs[i].bearingY - glyphs[i].height });
			verts.push_back({ (float)x + glyphs[i].bearingX                  , (float)glyphs[i].bearingY });
			verts.push_back({ (float)x + glyphs[i].bearingX + glyphs[i].width, (float)glyphs[i].bearingY });

			//Texture coordinates
			texs.push_back({ (float)glyphs[i].left, (float)glyphs[i].down });
			texs.push_back({ (float)glyphs[i].right, (float)glyphs[i].down });
			texs.push_back({ (float)glyphs[i].left, (float)glyphs[i].up });
			texs.push_back({ (float)glyphs[i].right, (float)glyphs[i].up });

			//Indices
			inds.push_back({ 0 + (4 * ind), 1 + (4 * ind), 2 + (4 * ind) });
			inds.push_back({ 1 + (4 * ind), 2 + (4 * ind), 3 + (4 * ind) });

			ind++;
		}
		//Move cursor
		x += glyphs[i].advance;
	}

	//Setup object
	XelaObject::addVertexData2fv(t->object, verts.data(), verts.size(), 0);
	XelaObject::addVertexData2fv(t->object, texs.data(), texs.size(), 1);
	XelaObject::addIndices(t->object, inds.data(), inds.size());
	XelaObject::updateData(t->object);

	//Add texture to shader
	XelaShader::addTexture(XelaText_shader, info.id, "text");
}

void XelaText::setFont(XelaText *t, XelaFont *f) {
	t->font = f;
	xelaGenTextObject(t);
}
void XelaText::setText(XelaText *t, const char *s) {
	if (s != t->text) {
		t->text = s;
		xelaGenTextObject(t);
	}
}

void XelaText::setColor(XelaText *t, XelaVec4<float> c) {
	t->color = c;
}
void XelaText::setPosition(XelaText *t, XelaVec3<float> p) {
	t->position = p;
}
void XelaText::setScale(XelaText *t, XelaVec2<float> s) {
	t->scale = s;
}

void XelaText::draw(XelaText *t, XelaVec2<int> screenResolution) {
	XelaShader::use(XelaText_shader);

	XelaFontTextureInfo info = t->font->info;

	glUniform2f(glGetUniformLocation(XelaText_shader->shaderProgram, "resolution"), screenResolution.x, screenResolution.y);
	glUniform3f(glGetUniformLocation(XelaText_shader->shaderProgram, "position"), t->position.x, t->position.y, t->position.z);
	glUniform2f(glGetUniformLocation(XelaText_shader->shaderProgram, "scale"), t->scale.x, t->scale.y);
	glUniform4f(glGetUniformLocation(XelaText_shader->shaderProgram, "textColor"), t->color.x, t->color.y, t->color.z, t->color.w);
	glUniform2i(glGetUniformLocation(XelaText_shader->shaderProgram, "textSize"), info.width, info.height);

	XelaObject::draw(t->object, 1);
}

XelaVec2<float> XelaText::getSize(XelaText *t) {
	XelaVec3<float> s = XelaObject::getSize(t->object);
	return { s.x, s.y };
}