#include "XelaText.h"

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

XelaText::XelaText(std::string fontFilePath, int size) {
	if (XelaText_shader == nullptr) {
		XelaText_shader = new XelaShader(XelaText_vSrc.c_str(), nullptr, XelaText_fSrc.c_str());
	}

	font = new XelaFont();
	font->loadFont(fontFilePath, size);
}
XelaText::XelaText(XelaFont *f) {
	if (XelaText_shader == nullptr) {
		XelaText_shader = new XelaShader(XelaText_vSrc.c_str(), nullptr, XelaText_fSrc.c_str());
	}

	font = f;
}

void XelaText::genTextObject() {
	//Create new XelaObject.
	if (object != nullptr) {
		delete object;
	}
	object = new XelaObject();

	//Load all glyphs for the text.
	std::vector<XelaGlyph> glyphs;
	int suc = 0;
	for (int i = 0; i < text.length(); i++) {
		glyphs.push_back(font->getGlyph(text[i], &suc));
	}
	//Generate font texture.
	font->genTexture();

	//Object data
	int x = 0;
	std::vector<XelaVec2<float>> verts;
	std::vector<XelaVec2<float>> texs;
	std::vector<XelaVec3<unsigned int>> inds;
	XelaFontTextureInfo info = font->getTexInfo();

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
	object->addVertexData(verts, 0);
	object->addVertexData(texs, 1);
	object->addIndices(inds);
	object->updateData();

	//Add texture to shader
	XelaText_shader->addTexture(info.id, "text");
}

void XelaText::setFont(std::string fontFilePath, int size) {
	delete font;
	font = new XelaFont();
	font->loadFont(fontFilePath, size);
	this->genTextObject();
}
void XelaText::setText(std::string t) {
	if (t != text) {
		text = t;
		this->genTextObject();
	}
}

void XelaText::setColor(XelaVec4<float> c) {
	color = c;
}
void XelaText::setPosition(XelaVec3<float> p) {
	position = p;
}
void XelaText::setScale(XelaVec2<float> s) {
	scale = s;
}

void XelaText::draw(XelaVec2<int> screenResolution) {
	XelaText_shader->use();

	XelaFontTextureInfo info = font->getTexInfo();

	glUniform2f(glGetUniformLocation(XelaText_shader->getProgram(), "resolution"), screenResolution.x, screenResolution.y);
	glUniform3f(glGetUniformLocation(XelaText_shader->getProgram(), "position"), position.x, position.y, position.z);
	glUniform2f(glGetUniformLocation(XelaText_shader->getProgram(), "scale"), scale.x, scale.y);
	glUniform4f(glGetUniformLocation(XelaText_shader->getProgram(), "textColor"), color.x, color.y, color.z, color.w);
	glUniform2i(glGetUniformLocation(XelaText_shader->getProgram(), "textSize"), info.width, info.height);

	object->draw(1);
}

XelaFont *XelaText::getFont() {
	return font;
}
XelaVec2<float> XelaText::getSize() {
	XelaVec3<float> s = object->getSize();
	return { s.x, s.y };
}