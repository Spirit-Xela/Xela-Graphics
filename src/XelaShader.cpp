//Xela Graphics
#include "XelaShader.h"

//C++
#if XELA_DEBUG_SHADER
#include <iostream>
#endif

static bool xelaGetBool(int type, void *data) {
	switch (type) {
		case XELA_BOOL:
			return *((bool *)data);
			break;
		case XELA_INT:
			return (bool)*((int *)data);
			break;
		case XELA_UNSIGNED_INT:
			return (bool)*((unsigned int *)data);
			break;
		case XELA_FLOAT:
			return (bool)*((float *)data);
			break;
		case XELA_DOUBLE:
			return (bool)*((double *)data);
			break;
	}
}
static int xelaGetInt(int type, void *data) {
	switch (type) {
		case XELA_BOOL:
			return (int)*((bool *)data);
			break;
		case XELA_INT:
			return *((int *)data);
			break;
		case XELA_UNSIGNED_INT:
			return (int)*((unsigned int *)data);
			break;
		case XELA_FLOAT:
			return (int)*((float *)data);
			break;
		case XELA_DOUBLE:
			return (int)*((double *)data);
			break;
	}
}
static unsigned int xelaGetUnsignedInt(int type, void *data) {
	switch (type) {
		case XELA_BOOL:
			return (unsigned int)*((bool *)data);
			break;
		case XELA_INT:
			return (unsigned int)*((int *)data);
			break;
		case XELA_UNSIGNED_INT:
			return *((unsigned int *)data);
			break;
		case XELA_FLOAT:
			return (unsigned int)*((float *)data);
			break;
		case XELA_DOUBLE:
			return (unsigned int)*((double *)data);
			break;
	}
}
static float xelaGetFloat(int type, void *data) {
	switch (type) {
		case XELA_BOOL:
			return (float)*((bool *)data);
			break;
		case XELA_INT:
			return (float)*((int *)data);
			break;
		case XELA_UNSIGNED_INT:
			return (float)*((unsigned int *)data);
			break;
		case XELA_FLOAT:
			return *((float *)data);
			break;
		case XELA_DOUBLE:
			return (float)*((double *)data);
			break;
	}
}
static double xelaGetDouble(int type, void *data) {
	switch (type) {
		case XELA_BOOL:
			return (double)*((bool *)data);
			break;
		case XELA_INT:
			return (double)*((int *)data);
			break;
		case XELA_UNSIGNED_INT:
			return (double)*((unsigned int *)data);
			break;
		case XELA_FLOAT:
			return (double)*((float *)data);
			break;
		case XELA_DOUBLE:
			return *((double *)data);
			break;
	}
}

static void xelaSetBoolUniform(XelaShader *s, XelaUniformInfo info) {
	switch (info.size) {
		case 1: {
			bool out = xelaGetBool(info.inFormat, info.data);
			glUniform1i(glGetUniformLocation(s->shaderProgram, info.name), out);
			break;
		}
		case 2: {
			XelaVec2<void *> *vec2 = (XelaVec2<void *> *)info.data;
			bool b1 = xelaGetBool(info.inFormat, vec2->x);
			bool b2 = xelaGetBool(info.inFormat, vec2->y);
			glUniform2i(glGetUniformLocation(s->shaderProgram, info.name), b1, b2);
			break;
		}
		case 3: {
			XelaVec3<void *> *vec3 = (XelaVec3<void *> *)info.data;
			bool b1 = xelaGetBool(info.inFormat, vec3->x);
			bool b2 = xelaGetBool(info.inFormat, vec3->y);
			bool b3 = xelaGetBool(info.inFormat, vec3->z);
			glUniform3i(glGetUniformLocation(s->shaderProgram, info.name), b1, b2, b3);
			break;
		}
		case 4: {
			XelaVec4<void *> *vec4 = (XelaVec4<void *> *)info.data;
			bool b1 = xelaGetBool(info.inFormat, vec4->x);
			bool b2 = xelaGetBool(info.inFormat, vec4->y);
			bool b3 = xelaGetBool(info.inFormat, vec4->z);
			bool b4 = xelaGetBool(info.inFormat, vec4->w);
			glUniform4i(glGetUniformLocation(s->shaderProgram, info.name), b1, b2, b3, b4);
			break;
		}
	}
}
static void xelaSetIntUniform(XelaShader *s, XelaUniformInfo info) {
	switch (info.size) {
		case 1: {
			int i = xelaGetInt(info.inFormat, info.data);
			glUniform1i(glGetUniformLocation(s->shaderProgram, info.name), i);
			break;
		}
		case 2: {
			XelaVec2<void *> *vec2 = (XelaVec2<void *> *)info.data;
			int i1 = xelaGetInt(info.inFormat, vec2->x);
			int i2 = xelaGetInt(info.inFormat, vec2->y);
			glUniform2i(glGetUniformLocation(s->shaderProgram, info.name), i1, i2);
			break;
		}
		case 3: {
			XelaVec3<void *> *vec3 = (XelaVec3<void *> *)info.data;
			int i1 = xelaGetInt(info.inFormat, vec3->x);
			int i2 = xelaGetInt(info.inFormat, vec3->y);
			int i3 = xelaGetInt(info.inFormat, vec3->z);
			glUniform3i(glGetUniformLocation(s->shaderProgram, info.name), i1, i2, i3);
			break;
		}
		case 4: {
			XelaVec4<void *> *vec4 = (XelaVec4<void *> *)info.data;
			int i1 = xelaGetInt(info.inFormat, vec4->x);
			int i2 = xelaGetInt(info.inFormat, vec4->y);
			int i3 = xelaGetInt(info.inFormat, vec4->z);
			int i4 = xelaGetInt(info.inFormat, vec4->w);
			glUniform4i(glGetUniformLocation(s->shaderProgram, info.name), i1, i2, i3, i4);
			break;
		}
	}
}
static void xelaSetUnsignedIntUniform(XelaShader *s, XelaUniformInfo info) {
	switch (info.size) {
		case 1: {
			unsigned int u = xelaGetUnsignedInt(info.inFormat, info.data);
			glUniform1ui(glGetUniformLocation(s->shaderProgram, info.name), u);
			break;
		}
		case 2: {
			XelaVec2<void *> *vec2 = (XelaVec2<void *> *)info.data;
			unsigned int u1 = xelaGetUnsignedInt(info.inFormat, vec2->x);
			unsigned int u2 = xelaGetUnsignedInt(info.inFormat, vec2->y);
			glUniform2ui(glGetUniformLocation(s->shaderProgram, info.name), u1, u2);
			break;
		}
		case 3: {
			XelaVec3<void *> *vec3 = (XelaVec3<void *> *)info.data;
			unsigned int u1 = xelaGetUnsignedInt(info.inFormat, vec3->x);
			unsigned int u2 = xelaGetUnsignedInt(info.inFormat, vec3->y);
			unsigned int u3 = xelaGetUnsignedInt(info.inFormat, vec3->z);
			glUniform3ui(glGetUniformLocation(s->shaderProgram, info.name), u1, u2, u3);
			break;
		}
		case 4: {
			XelaVec4<void *> *vec4 = (XelaVec4<void *> *)info.data;
			unsigned int u1 = xelaGetUnsignedInt(info.inFormat, vec4->x);
			unsigned int u2 = xelaGetUnsignedInt(info.inFormat, vec4->y);
			unsigned int u3 = xelaGetUnsignedInt(info.inFormat, vec4->z);
			unsigned int u4 = xelaGetUnsignedInt(info.inFormat, vec4->w);
			glUniform4ui(glGetUniformLocation(s->shaderProgram, info.name), u1, u2, u3, u4);
			break;
		}
	}
}
static void xelaSetFloatUniform(XelaShader *s, XelaUniformInfo info) {
	switch (info.size) {
		case 1: {
			float f = xelaGetFloat(info.inFormat, info.data);
			glUniform1f(glGetUniformLocation(s->shaderProgram, info.name), f);
			break;
		}
		case 2: {
			XelaVec2<void *> *vec2 = (XelaVec2<void *> *)info.data;
			float f1 = xelaGetFloat(info.inFormat, vec2->x);
			float f2 = xelaGetFloat(info.inFormat, vec2->y);
			glUniform2f(glGetUniformLocation(s->shaderProgram, info.name), f1, f2);
			break;
		}
		case 3: {
			XelaVec3<void *> *vec3 = (XelaVec3<void *> *)info.data;
			float f1 = xelaGetFloat(info.inFormat, vec3->x);
			float f2 = xelaGetFloat(info.inFormat, vec3->y);
			float f3 = xelaGetFloat(info.inFormat, vec3->z);
			glUniform3f(glGetUniformLocation(s->shaderProgram, info.name), f1, f2, f3);
			break;
		}
		case 4: {
			XelaVec4<void *> *vec4 = (XelaVec4<void *> *)info.data;
			float f1 = xelaGetFloat(info.inFormat, vec4->x);
			float f2 = xelaGetFloat(info.inFormat, vec4->y);
			float f3 = xelaGetFloat(info.inFormat, vec4->z);
			float f4 = xelaGetFloat(info.inFormat, vec4->w);
			glUniform4f(glGetUniformLocation(s->shaderProgram, info.name), f1, f2, f3, f4);
			break;
		}
	}
}
static void xelaSetDoubleUniform(XelaShader *s, XelaUniformInfo info) {
	switch (info.size) {
		case 1: {
			double d = xelaGetDouble(info.inFormat, info.data);
			glUniform1d(glGetUniformLocation(s->shaderProgram, info.name), d);
			break;
		}
		case 2: {
			XelaVec2<void *> *vec2 = (XelaVec2<void *> *)info.data;
			double d1 = xelaGetDouble(info.inFormat, vec2->x);
			double d2 = xelaGetDouble(info.inFormat, vec2->y);
			glUniform2d(glGetUniformLocation(s->shaderProgram, info.name), d1, d2);
			break;
		}
		case 3: {
			XelaVec3<void *> *vec3 = (XelaVec3<void *> *)info.data;
			double d1 = xelaGetDouble(info.inFormat, vec3->x);
			double d2 = xelaGetDouble(info.inFormat, vec3->y);
			double d3 = xelaGetDouble(info.inFormat, vec3->z);
			glUniform3d(glGetUniformLocation(s->shaderProgram, info.name), d1, d2, d3);
			break;
		}
		case 4: {
			XelaVec4<void *> *vec4 = (XelaVec4<void *> *)info.data;
			double d1 = xelaGetDouble(info.inFormat, vec4->x);
			double d2 = xelaGetDouble(info.inFormat, vec4->y);
			double d3 = xelaGetDouble(info.inFormat, vec4->z);
			double d4 = xelaGetDouble(info.inFormat, vec4->w);
			glUniform4d(glGetUniformLocation(s->shaderProgram, info.name), d1, d2, d3, d4);
			break;
		}
	}
}
static void xelaSetUniforms(XelaShader *s) {
	//Set texture uniforms.
	for (int i = 0; i < s->texList.size(); i++) {
		XelaImageInfo curr = s->texList[i]->info;

		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, curr.id);
		glUniform1i(glGetUniformLocation(s->shaderProgram, curr.name), i);
	}
	//Set other uniforms.
	for (int i = 0; i < s->uniforms.size(); i++) {
		switch (s->uniforms[i].outFormat) {
			case XELA_BOOL:
				xelaSetBoolUniform(s, s->uniforms[i]);
				break;
			case XELA_INT:
				xelaSetIntUniform(s, s->uniforms[i]);
				break;
			case XELA_UNSIGNED_INT:
				xelaSetUnsignedIntUniform(s, s->uniforms[i]);
				break;
			case XELA_FLOAT:
				xelaSetFloatUniform(s, s->uniforms[i]);
				break;
			case XELA_DOUBLE:
				xelaSetDoubleUniform(s, s->uniforms[i]);
				break;
		}
	}
}

static void xelaCompileShader(XelaShader *s, std::string srcVert, std::string srcGeo, std::string srcFrag) {
	const char *vSrc = srcVert.c_str();
	const char *gSrc = srcGeo.c_str();
	const char *fSrc = srcFrag.c_str();

	int success;
	char infoLog[512];

	if (s->vertexShader != -1) {
		//This shader has been compiled before, remove the redundant shader.
		glDeleteShader(s->vertexShader);
	}

	//Create vertex shader.
	s->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(s->vertexShader, 1, &vSrc, nullptr);
	glCompileShader(s->vertexShader);

	//Error check.
	glGetShaderiv(s->vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		#if XELA_DEBUG_SHADER
		//Print error.
		glGetShaderInfoLog(s->vertexShader, 512, nullptr, infoLog);
		std::cout << "[ERROR][XelaShader] Error compiling vertex shader: " << infoLog << std::endl;
		#endif
		//Delete shader and return.
		glDeleteShader(s->vertexShader);
		return;
	}

	if (s->geometryShader != -1) {
		//This shader has been compiled before, remove the redundant shader.
		glDeleteShader(s->geometryShader);
		s->geometryShader = -1;
	}

	//Create geometry shader if one is defined.
	if (srcGeo != "") {
		s->geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(s->geometryShader, 1, &gSrc, nullptr);
		glCompileShader(s->geometryShader);

		//Error check.
		glGetShaderiv(s->geometryShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			#if XELA_DEBUG_SHADER
			//Print error.
			glGetShaderInfoLog(s->geometryShader, 512, nullptr, infoLog);
			std::cout << "[ERROR][XelaShader] Error compiling geometry shader: " << infoLog << std::endl;
			#endif
			//Delete shader and return.
			glDeleteShader(s->geometryShader);
			return;
		}
	}

	if (s->fragmentShader != -1) {
		//This shader has been compiled before, remove the redundant shader.
		glDeleteShader(s->fragmentShader);
	}

	//Create fragment shader.
	s->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(s->fragmentShader, 1, &fSrc, nullptr);
	glCompileShader(s->fragmentShader);

	//Error check.
	glGetShaderiv(s->fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		#if XELA_DEBUG_SHADER
		//Print error.
		glGetShaderInfoLog(s->fragmentShader, 512, nullptr, infoLog);
		std::cout << "[ERROR][XelaShader] Error compiling fragment shader: " << infoLog << std::endl;
		#endif
		//Delete shaders and return.
		glDeleteShader(s->vertexShader);
		glDeleteShader(s->fragmentShader);
		return;
	}

	if (s->shaderProgram != -1) {
		//This shader has been compiled before, remove the redundant shader.
		glDeleteProgram(s->shaderProgram);
	}

	//Create program.
	s->shaderProgram = glCreateProgram();
	glAttachShader(s->shaderProgram, s->vertexShader);
	if (srcGeo != "") {
		glAttachShader(s->shaderProgram, s->geometryShader);
	}
	glAttachShader(s->shaderProgram, s->fragmentShader);
	glLinkProgram(s->shaderProgram);

	//Error Check.
	glGetProgramiv(s->shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
	}
}
XelaShader *XelaShader::genShader(const char *shaderV, const char *shaderG, const char *shaderF) {
	XelaShader *shader = new XelaShader();
	std::string vert = "", geo = "", frag = "";

	vert = std::string(shaderV);
	if (shaderG != nullptr) {
		geo = std::string(shaderG);
	}
	frag = std::string(shaderF);

	xelaCompileShader(shader, vert, geo, frag);

	return shader;
}
XelaShader *XelaShader::copyShader(XelaShader *s) {
	XelaShader *shader = new XelaShader();
	shader->shaderProgram = s->shaderProgram;
	return shader;
}

void XelaShader::setShader(XelaShader *s, const char *shaderV, const char *shaderG, const char *shaderF) {
	//Update shader src based on type and recompile.
	std::string vert, geo, frag;

	vert = std::string(shaderV);
	if (shaderG != nullptr) {
		geo = std::string(shaderG);
	}
	frag = std::string(shaderF);
	
	xelaCompileShader(s, vert, geo, frag);
}

void XelaShader::genImage(XelaShader *s, const char *tPath, const char *name, int *width, int *height, int *numChannels, int inputFormat, int textureFormat) {
	XelaImage *add = XelaImage::genImage(name, tPath, width, height, numChannels, inputFormat, textureFormat);
	s->texList.push_back(add);
}
void XelaShader::addImage(XelaShader *s, XelaImage *i) {
	s->texList.push_back(i);
}

void XelaShader::addTexture(XelaShader *s, GLuint id, const char *name) {
	XelaImage *add = new XelaImage();
	XelaImage::setName(add, name);
	XelaImage::setID(add, id);
	s->texList.push_back(add);
}

void XelaShader::addShaderCallback(XelaShader *s, ShaderCallbackFunction func) {
	s->shaderCB.push_back(func);
}
void XelaShader::removeShaderCallback(XelaShader *s, ShaderCallbackFunction func) {
	for (int i = 0; i < s->shaderCB.size(); i++) {
		if (s->shaderCB[i] == func) {
			s->shaderCB.erase(s->shaderCB.begin() + i, s->shaderCB.begin() + i + 1);
		}
	}
}

void XelaShader::use(XelaShader *s) {
	glUseProgram(s->shaderProgram);
	xelaSetUniforms(s);
	for (int i = 0; i < (int)s->shaderCB.size(); i++) {
		s->shaderCB[i](s->shaderProgram);
	}
}

void XelaShader::addUniform(XelaShader *s, const char *name, int inType, int outType, void *data) {
	XelaUniformInfo info;
	info.name = name;
	info.size = 1;
	info.inFormat = inType;
	info.outFormat = outType;
	info.data = data;
	s->uniforms.push_back(info);
}
void XelaShader::addUniformVec2(XelaShader *s, const char *name, int inType, int outType, void *data1, void *data2) {
	XelaUniformInfo info;
	info.name = name;
	info.size = 2;
	info.inFormat = inType;
	info.outFormat = outType;
	info.data = new XelaVec2<void *>({ data1, data2 });
	s->uniforms.push_back(info);
}
void XelaShader::addUniformVec3(XelaShader *s, const char *name, int inType, int outType, void *data1, void *data2, void *data3) {
	XelaUniformInfo info;
	info.name = name;
	info.size = 3;
	info.inFormat = inType;
	info.outFormat = outType;
	info.data = new XelaVec3<void *>({ data1, data2, data3 });
	s->uniforms.push_back(info);
}
void XelaShader::addUniformVec4(XelaShader *s, const char *name, int inType, int outType, void *data1, void *data2, void *data3, void *data4) {
	XelaUniformInfo info;
	info.name = name;
	info.size = 4;
	info.inFormat = inType;
	info.outFormat = outType;
	info.data = new XelaVec4<void *>({ data1, data2, data3, data4 });
	s->uniforms.push_back(info);
}