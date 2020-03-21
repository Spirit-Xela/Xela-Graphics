#ifndef _XELA_SHADER_H
#define _XELA_SHADER_H

//Libs
#include "GL/glew.h"
#include "GLFW/glfw3.h"
//Xela Graphics
#include "XelaGraphics.h"
#include "XelaImage.h"
//C++
#include <vector>
#include <string>

extern "C" {
	struct XelaShader {
		//Shader locations
		unsigned int vertexShader = -1, geometryShader = -1, fragmentShader = -1, shaderProgram = -1;

		//List of textures for this shader
		std::vector<XelaImage *> texList;

		//List of functions to call whenever this shader is used
		std::vector<ShaderCallbackFunction> shaderCB;

		//Store uniforms
		std::vector<XelaUniformInfo> uniforms;

		//Creates a new XelaShader and compiles the given GLSL source code.
		//shaderV and ShaderF are required. However, shaderG may be nullptr.
		XELAGRAPHICS_API static XelaShader *genShader(const char *shaderV, const char *shaderG, const char *shaderF);
		//Creates a new XelaShader with the same shader as s.
		//This is used for having multiple shader objects with different textures/uniforms without compiling the same source code multiple times.
		XELAGRAPHICS_API static XelaShader *copyShader(XelaShader *s);

		//Sets the shader to use
		//shaderV and ShaderF are required. However, shaderG may be nullptr
		XELAGRAPHICS_API static void setShader(XelaShader *s, const char *shaderV, const char *shaderG, const char *shaderF);

		//Loads an image from the file path specified and adds it to a list of textures to send to the shader as uniforms under the name specified.
		XELAGRAPHICS_API static void genImage(XelaShader *s, const char *tPath, const char *name, int *width, int *height, int *numChannels, int inputFormat, int textureFormat);
		//Add an image to the list of textures to send to the shader as uniforms
		XELAGRAPHICS_API static void addImage(XelaShader *s, XelaImage *i);

		//Adds the specified texture id to a list of textures to send to the shader as uniforms under the name specified
		XELAGRAPHICS_API static void addTexture(XelaShader *s, GLuint id, const char *name);

		//Defines a callback function to be called whenever this shader is applied
		//Use this function to declare uniforms or perform other operations dependent on the shader being activated first
		XELAGRAPHICS_API static void addShaderCallback(XelaShader *s, ShaderCallbackFunction func);
		//Removes a function from the list of functions to be called whenever this shader is applied
		XELAGRAPHICS_API static void removeShaderCallback(XelaShader *s, ShaderCallbackFunction func);

		//Activates this shader
		XELAGRAPHICS_API static void use(XelaShader *s);

		//Add a pointer to some data to send to this shader as a uniform whenever this shader is used.
		//This will be sent to name in the shader.
		//The type of this uniform should be outType (bool, int, etc).
		//Data should be of type inType.
		//This is meant to be used to uniforms which will always be set to a single variable.
		//This should not be used if you plan on setting a uniform to multiple different variables in between draw calls.
		XELAGRAPHICS_API static void addUniform(XelaShader *s, const char *name, int inType, int outType, void *data);
		//Add a pointer to some vec2 data to send to this shader as a uniform whenever this shader is used.
		//This will be sent to name in the shader
		//The type of this uniform should be a vec2 of outType (bvec2, ivec2, etc).
		//Data should be of type inType.
		//This is meant to be used to uniforms which will always be set to a single variable.
		//This should not be used if you plan on setting a uniform to multiple different variables in between draw calls.
		XELAGRAPHICS_API static void addUniformVec2(XelaShader *s, const char *name, int inType, int outType, void *data1, void *data2);
		//Add a pointer to some vec3 data to send to this shader as a uniform whenever this shader is used.
		//This will be sent to name in the shader
		//The type of this uniform should be a vec3 of outType (bvec3, ivec3, etc).
		//Data should be of type inType.
		//This is meant to be used to uniforms which will always be set to a single variable.
		//This should not be used if you plan on setting a uniform to multiple different variables in between draw calls.
		XELAGRAPHICS_API static void addUniformVec3(XelaShader *s, const char *name, int inType, int outType, void *data1, void *data2, void *data3);
		//Add a pointer to some vec4 data to send to this shader as a uniform whenever this shader is used.
		//This will be sent to name in the shader
		//The type of this uniform should be a vec4 of outType (bvec4, ivec4, etc).
		//Data should be of type inType.
		//This is meant to be used to uniforms which will always be set to a single variable.
		//This should not be used if you plan on setting a uniform to multiple different variables in between draw calls.
		XELAGRAPHICS_API static void addUniformVec4(XelaShader *s, const char *name, int inType, int outType, void *data1, void *data2, void *data3, void *data4);
	};
}

#endif