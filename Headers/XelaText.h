#ifndef _XELA_TEXT_H
#define _XELA_TEXT_H

//Xela Graphics
#include "XelaGraphics.h"
#include "XelaObject.h"
#include "XelaFont.h"
//C++
#include <string>

extern "C" {
	struct XelaText {
		XelaObject *object = nullptr;

		XelaFont *font = nullptr;

		//Text information
		std::string text = "";
		XelaVec4<float> color = { 1, 1, 1, 1 };
		XelaVec3<float> position = { 0, 0, 0 };
		XelaVec2<float> scale = { 1, 1 };

		XELAGRAPHICS_API static XelaText *genText(XelaFont *f);

		//Loads a new font for this text
		XELAGRAPHICS_API static void setFont(XelaText *t, XelaFont *f);
		//Sets the text to be displayed
		XELAGRAPHICS_API static void setText(XelaText *t, const char *s);

		//Sets the color of the text being displayed
		XELAGRAPHICS_API static void setColor(XelaText *t, XelaVec4<float> c);
		//Sets the position of the text
		//Note that this doesn't use OpenGLs [-1, 1] range but instead uses the range [0, resolution], where resolution is passed as
		//and argument to XelaText.draw()
		XELAGRAPHICS_API static void setPosition(XelaText *t, XelaVec3<float> p);
		//Sets the scale to multiply this object's size by. This does not scale the position, only the size.
		XELAGRAPHICS_API static void setScale(XelaText *t, XelaVec2<float> s);

		//Draws the text based on the specified screen resolution
		XELAGRAPHICS_API static void draw(XelaText *t, XelaVec2<int> screenResolution);

		//Returns the size of this text object. Does not include scale.
		XELAGRAPHICS_API static XelaVec2<float> getSize(XelaText *t);
	};
}

#endif