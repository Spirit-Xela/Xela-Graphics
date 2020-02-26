#ifndef _XELA_TEXT_H
#define _XELA_TEXT_H

//Engine
#include "XelaDefinitions.h"
#include "XelaObject.h"
#include "XelaShader.h"
#include "XelaFont.h"
//C++
#include <string>
#include <vector>

class XelaText {
private:
	XelaObject *object = nullptr;

	XelaFont *font = nullptr;

	//Text information
	std::string text = "";
	XelaVec4<float> color = { 1, 1, 1, 1 };
	XelaVec3<float> position = { 0, 0, 0 };
	XelaVec2<float> scale = { 1, 1 };

	//Generates the XelaObject for this text object.
	void genTextObject();
public:
	//Creates a new XelaText object using the font file specified by fontFilePath rendered at size pixels.
	XelaText(std::string fontFilePath, int size);
	//Creates a new XelaText object using a pre-existing XelaFont object.
	XelaText(XelaFont *f);

	//Loads a new font for this text
	void setFont(std::string fontFilePath, int size);
	//Sets the text to be displayed
	void setText(std::string t);

	//Sets the color of the text being displayed
	void setColor(XelaVec4<float> c);
	//Sets the position of the text
	//Note that this doesn't use OpenGLs [-1, 1] range but instead uses the range [0, resolution], where resolution is passed as
	//and argument to XelaText.draw()
	void setPosition(XelaVec3<float> p);
	//Sets the scale to multiply this object's size by. This does not scale the position, only the size.
	void setScale(XelaVec2<float> s);

	//Draws the text based on the specified screen resolution
	void draw(XelaVec2<int> screenResolution);

	//Returns a pointer to the XelaFont object being used by this text object.
	XelaFont *getFont();
	//Returns the size of this text object. Does not include scale.
	XelaVec2<float> getSize();
};

#endif