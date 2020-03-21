#include <iostream>
#include <vector>

#include <XelaWindow.h>
#include <XelaEvents.h>
#include <XelaText.h>
#include <XelaObject.h>
#include <XelaShader.h>

//Vertex shader source code
const char *vertexShaderSrc =
"#version 330 core\n"
//The location here corresponds to the id of the vertex data being passed to square
"layout (location = 0) in vec2 vertex;\n"

"void main() {\n"
"   gl_Position = vec4(vertex.xy, 0, 1);\n"
"}";

//Fragment shader source code
const char *fragmentShaderSrc =
"#version 330 core\n"
"out vec4 aColor;\n"
"uniform vec4 color;\n"

"void main() {\n"
"   aColor = color;\n"
"}";

XelaWindow *window = nullptr;
XelaText *hello = nullptr;
XelaFont *font = nullptr;
XelaObject *square = nullptr;
XelaShader *shader = nullptr;

XelaVec4<float> color = { 1.0f, 1.0f, 1.0f, 1.0f };

#define RESOLUTION_X 720
#define RESOLUTION_Y 720

void loop() {
	//Draw text. XelaText uses its own shader so there's no need to create one for this.
	XelaText::draw(hello, { RESOLUTION_X, RESOLUTION_Y });

	//XelaObject doesn't have its own shader, so make sure to create a shader for it and use that before drawing an object.
	XelaShader::use(shader);
	XelaObject::draw(square, 1);

	//Update the window at the end of the loop.
	XelaWindow::update(window);
}

void keyCallback(XelaWindow *window, int key, int scancode, int action, int mods) {
	switch (key) {
		case XELA_ESCAPE:
			//Once the escape key is released set shouldClose to true, which will cause the loop to stop running and the program to close.
			if (action == XELA_RELEASE) {
				XelaWindow::setShouldClose(window, true);
			}
			break;
		//Change the color of the square with keys 1-8
		case XELA_1:
			color = { 0.0f, 0.0f, 0.0f, 1.0f };
			break;
		case XELA_2:
			color = { 0.0f, 0.0f, 1.0f, 1.0f };
			break;
		case XELA_3:
			color = { 0.0f, 1.0f, 0.0f, 1.0f };
			break;
		case XELA_4:
			color = { 0.0f, 1.0f, 1.0f, 1.0f };
			break;
		case XELA_5:
			color = { 1.0f, 0.0f, 0.0f, 1.0f };
			break;
		case XELA_6:
			color = { 1.0f, 0.0f, 1.0f, 1.0f };
			break;
		case XELA_7:
			color = { 1.0f, 1.0f, 0.0f, 1.0f };
			break;
		case XELA_8:
			color = { 1.0f, 1.0f, 1.0f, 1.0f };
			break;
	}
}

void setupText() {
	//Create a font for the text.
	font = XelaFont::genFont();
	XelaFont::loadFont(font, "C:/Tests/ArialRoundBold.ttf", 32);

	//Create a new XelaText that uses the font that was just created.
	hello = XelaText::genText(font);
	XelaText::setText(hello, "Hello, world!");
	XelaText::setColor(hello, { 0.0f, 0.0f, 0.0f, 1.0f });
	
	//Center the text on the screen
	XelaVec2<float> size = XelaText::getSize(hello);
	XelaText::setPosition(hello, { (RESOLUTION_X / 2) - (size.x / 2), RESOLUTION_Y / 2, -0.5f });
}
void setupSquare() {
	//Vertices/indices of the object
	std::vector<XelaVec2<float>> vertices = { { -0.5f, -0.5f }, { 0.5f, -0.5f }, { -0.5f, 0.5f }, { 0.5f, 0.5f } };
	std::vector<XelaVec3<unsigned int>> indices = { { 0, 1, 2 }, { 1, 2, 3 } };

	//Create a new XelaObject
	square = XelaObject::genObject();
	//Give square the vertices/indices defined above. The 0 in addVertexData is the id of this vertex data, which corresponds to the location
	//of the vertex variable in the shader source code.
	XelaObject::addVertexData2fv(square, vertices.data(), vertices.size(), 0);
	XelaObject::addIndices(square, indices.data(), indices.size());
	//Always call updateData when vertex data/indices are changed. Not calling this can cause errors or cause the program to crash.
	XelaObject::updateData(square);
}
void setupShader() {
	//Create a new XelaShader using the shader source code. gShader is set to nullptr because a geometry shader isn't used here.
	shader = XelaShader::genShader(vertexShaderSrc, nullptr, fragmentShaderSrc);
	//Set color as a vec4 uniform in this shader. Whenever this shader is used, the values in color will be passed as a uniform to the shader.
	XelaShader::addUniformVec4(shader, "color", XELA_FLOAT, XELA_FLOAT, &color.x, &color.y, &color.z, &color.w);
}

int main() {
	//Always start with creating a window. Xela Graphics will automatically initialize glfw/glew when the first window is created.
	int success;
	window = XelaWindow::genWindow(RESOLUTION_X, RESOLUTION_Y, "Hello World", false, &success, true);
	if (success != XELA_SUCCESS) {
		std::cout << "Window creation failed." << std::endl;
		return 0;
	}

	//Setup
	xelaSetKeyCallback(&keyCallback);
	setupShader();
	setupSquare();
	setupText();

	//Keep running the render loop so long as shouldClose is false.
	while (!XelaWindow::shouldClose(window)) {
		loop();
	}

	return 0;
}