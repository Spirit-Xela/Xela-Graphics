#ifndef _XELA_SHADER_H
#define _XELA_SHADER_H

//OpenGL
#include "GL/glew.h"
#include "GLFW/glfw3.h"
//Engine
#include "XelaDefinitions.h"
//C++
#include <vector>
#include <string>
#ifdef XELA_DEBUG_SHADER
	#include <iostream>
#endif

//stb_image function wrap
void xela_wrap_stbi_set_flip_vertically_on_load(bool val);
//stb_image function wrap
void xela_wrap_stbi_image_free(void *data);
//stb_image function wrap
unsigned char* xela_wrap_stbi_load(const char *path, int *width, int *height, int *channels, int som);

class XelaShader {
private:
	//Shader locations
	unsigned int vertexShader = -1, geometryShader = -1, fragmentShader = -1, shaderProgram = -1;

	//Vertex shader source code
	std::string srcVert = "";
	//Geometry shader source code
	std::string srcGeo = "";
	//Fragment shader source code
	std::string srcFrag = "";

	//List of textures for this shader
	std::vector<XelaImageInfo> texList;

	//List of functions to call whenever this shader is used
	std::vector<XelaShaderCallbackFunction> shaderCB;

	//Store uniforms
	std::vector<XelaUniformInfo> uniforms;

	//Compile the shader
	void compile();

	bool getBool(int type, void *data);
	int getInt(int type, void *data);
	unsigned int getUnsignedInt(int type, void *data);
	float getFloat(int type, void *data);
	double getDouble(int type, void *data);

	void setBoolUniform(XelaUniformInfo info);
	void setIntUniform(XelaUniformInfo info);
	void setUnsignedIntUniform(XelaUniformInfo info);
	void setFloatUniform(XelaUniformInfo info);
	void setDoubleUniform(XelaUniformInfo info);
	void setUniforms();
public:
	//Creates a new XelaShader and compiles the given GLSL source code.
	//shaderV and ShaderF are required. However, shaderG may be nullptr.
	XelaShader(const char *shaderV, const char *shaderG, const char *shaderF);
	//Creates a new XelaShader with the same shader as s.
	//This is used for having multiple shader objects with different textures/uniforms without compiling the same source code multiple times.
	XelaShader(XelaShader *s);

	//Sets the shader to use
	//shaderV and ShaderF are required. However, shaderG may be nullptr
	void setShader(const char *shaderV, const char *shaderG, const char *shaderF);
	//Loads an image from the file path specified and adds it to a list of textures to send to the shader as uniforms under the name specified.
	void addImage(const char *tPath, const char *name, int *width, int *height, int *numChannels, int inputFormat, int textureFormat);
	//Adds the specified texture id to a list of textures to send to the shader as uniforms under the name specified
	void addTexture(GLuint id, const char *name);
	//Defines a callback function to be called whenever this shader is applied
	//Use this function to declare uniforms or perform other operations dependent on the shader being activated first
	void addShaderCallback(XelaShaderCallbackFunction func);
	//Removes a function from the list of functions to be called whenever this shader is applied
	void removeShaderCallback(XelaShaderCallbackFunction func);
	//Activates this shader
	void use();

	//Add a pointer to some data to send to this shader as a uniform whenever this shader is used.
	//This will be sent to name in the shader.
	//The type of this uniform should be outType (bool, int, etc).
	//Data should be of type inType.
	//This is meant to be used to uniforms which will always be set to a single variable.
	//This should not be used if you plan on setting a uniform to multiple different variables in between draw calls.
	void addUniform(const char *name, int inType, int outType, void *data);
	//Add a pointer to some vec2 data to send to this shader as a uniform whenever this shader is used.
	//This will be sent to name in the shader
	//The type of this uniform should be a vec2 of outType (bvec2, ivec2, etc).
	//Data should be of type inType.
	//This is meant to be used to uniforms which will always be set to a single variable.
	//This should not be used if you plan on setting a uniform to multiple different variables in between draw calls.
	void addUniformVec2(const char *name, int inType, int outType, void *data1, void *data2);
	//Add a pointer to some vec3 data to send to this shader as a uniform whenever this shader is used.
	//This will be sent to name in the shader
	//The type of this uniform should be a vec3 of outType (bvec3, ivec3, etc).
	//Data should be of type inType.
	//This is meant to be used to uniforms which will always be set to a single variable.
	//This should not be used if you plan on setting a uniform to multiple different variables in between draw calls.
	void addUniformVec3(const char *name, int inType, int outType, void *data1, void *data2, void *data3);
	//Add a pointer to some vec4 data to send to this shader as a uniform whenever this shader is used.
	//This will be sent to name in the shader
	//The type of this uniform should be a vec4 of outType (bvec4, ivec4, etc).
	//Data should be of type inType.
	//This is meant to be used to uniforms which will always be set to a single variable.
	//This should not be used if you plan on setting a uniform to multiple different variables in between draw calls.
	void addUniformVec4(const char *name, int inType, int outType, void *data1, void *data2, void *data3, void *data4);

	//Returns a list of information on each texture associated with this shader
	std::vector<XelaImageInfo> getTexList();
	//Returns the program id for this shader
	unsigned int getProgram();
};

#endif