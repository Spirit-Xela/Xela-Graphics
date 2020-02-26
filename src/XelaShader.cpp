#include "XelaShader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//These functions are wrapped in case they need to be used somewhere else since the stb_image implementation is setup here.
void xela_wrap_stbi_set_flip_vertically_on_load(bool val) {
	stbi_set_flip_vertically_on_load(val);
}
void xela_wrap_stbi_image_free(void *data) {
	stbi_image_free(data);
}
unsigned char *xela_wrap_stbi_load(const char *path, int *width, int *height, int *channels, int reqChannels) {
	return stbi_load(path, width, height, channels, reqChannels);
}

XelaShader::XelaShader(const char *shaderV, const char *shaderG, const char *shaderF) {
	srcVert = std::string(shaderV);
	if (shaderG != nullptr) {
		srcGeo = std::string(shaderG);
	}
	srcFrag = std::string(shaderF);
	this->compile();
}
XelaShader::XelaShader(XelaShader *s) {
	shaderProgram = s->getProgram();
}

void XelaShader::compile() {
	const char *vSrc = srcVert.c_str();
	const char *gSrc = srcGeo.c_str();
	const char *fSrc = srcFrag.c_str();

	int success;
	char infoLog[512];

	if (vertexShader != -1) {
		//This shader has been compiled before, remove the redundant shader.
		glDeleteShader(vertexShader);
	}

	//Create vertex shader.
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vSrc, nullptr);
	glCompileShader(vertexShader);

	//Error check.
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
#ifdef XELA_DEBUG_SHADER
		//Print error.
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "[ERROR][XelaShader] Error compiling vertex shader: " << infoLog << std::endl;
#endif
		//Delete shader and return.
		glDeleteShader(vertexShader);
		return;
	}

	if (geometryShader != -1) {
		//This shader has been compiled before, remove the redundant shader.
		glDeleteShader(geometryShader);
		geometryShader = -1;
	}

	//Create geometry shader if one is defined.
	if (srcGeo != "") {
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &gSrc, nullptr);
		glCompileShader(geometryShader);

		//Error check.
		glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
		if (!success) {
#ifdef XELA_DEBUG_SHADER
			//Print error.
			glGetShaderInfoLog(geometryShader, 512, nullptr, infoLog);
			std::cout << "[ERROR][XelaShader] Error compiling geometry shader: " << infoLog << std::endl;
#endif
			//Delete shader and return.
			glDeleteShader(geometryShader);
			return;
		}
	}

	if (fragmentShader != -1) {
		//This shader has been compiled before, remove the redundant shader.
		glDeleteShader(fragmentShader);
	}

	//Create fragment shader.
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fSrc, nullptr);
	glCompileShader(fragmentShader);

	//Error check.
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
#ifdef XELA_DEBUG_SHADER
		//Print error.
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "[ERROR][XelaShader] Error compiling fragment shader: " << infoLog << std::endl;
#endif
		//Delete shaders and return.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return;
	}

	if (shaderProgram != -1) {
		//This shader has been compiled before, remove the redundant shader.
		glDeleteProgram(shaderProgram);
	}

	//Create program.
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	if (srcGeo != "") {
		glAttachShader(shaderProgram, geometryShader);
	}
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Error Check.
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
	}

	//Cleanup
	delete vSrc;
	if (srcGeo != "") {
		delete gSrc;
	}
	delete fSrc;
	srcVert = "";
	srcGeo = "";
	srcFrag = "";
}
void XelaShader::setShader(const char *shaderV, const char *shaderG, const char *shaderF) {
	//Update shader src based on type and recompile.
	srcVert = shaderV;
	srcGeo = shaderG;
	srcFrag = shaderF;
	this->compile();
}

void XelaShader::addImage(const char *tPath, const char *name, int *width, int *height, int *numChannels, int inputFormat, int textureFormat) {
	//Load data with stb_image.
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(tPath, width, height, numChannels, 0);

	//Add new entry in texList.
	texList.push_back({ name, 0 });

	//Generate OpenGL texture.
	glGenTextures(1, &texList[texList.size() - 1].id);
	glBindTexture(GL_TEXTURE_2D, texList[texList.size() - 1].id);
	glTexImage2D(GL_TEXTURE_2D, 0, inputFormat, *width, *height, 0, textureFormat, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	//Free data.
	stbi_image_free(data);
}
void XelaShader::addTexture(GLuint id, const char *name) {
	bool found = false;
	for (int i = 0; i < texList.size(); i++) {
		if (std::string(texList[i].name) == std::string(name)) {
			texList[i].id = id;
			found = true;
			break;
		}
	}
	if (!found) {
		texList.push_back({ name, id });
	}
}

void XelaShader::addShaderCallback(XelaShaderCallbackFunction func) {
	shaderCB.push_back(func);
}
void XelaShader::removeShaderCallback(XelaShaderCallbackFunction func) {
	for (int i = 0; i < shaderCB.size(); i++) {
		if (shaderCB[i] == func) {
			shaderCB.erase(shaderCB.begin() + i, shaderCB.begin() + i + 1);
		}
	}
}

bool XelaShader::getBool(int type, void *data) {
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
int XelaShader::getInt(int type, void *data) {
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
unsigned int XelaShader::getUnsignedInt(int type, void *data) {
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
float XelaShader::getFloat(int type, void *data) {
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
double XelaShader::getDouble(int type, void *data) {
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

void XelaShader::setBoolUniform(XelaUniformInfo info) {
	switch (info.size) {
		case 1: {
			bool out = getBool(info.inFormat, info.data);
			glUniform1i(glGetUniformLocation(shaderProgram, info.name), out);
			break;
		}
		case 2: {
			XelaVec2<void *> *vec2 = (XelaVec2<void *> *)info.data;
			bool b1 = getBool(info.inFormat, vec2->x);
			bool b2 = getBool(info.inFormat, vec2->y);
			glUniform2i(glGetUniformLocation(shaderProgram, info.name), b1, b2);
			break;
		}
		case 3: {
			XelaVec3<void *> *vec3 = (XelaVec3<void *> *)info.data;
			bool b1 = getBool(info.inFormat, vec3->x);
			bool b2 = getBool(info.inFormat, vec3->y);
			bool b3 = getBool(info.inFormat, vec3->z);
			glUniform3i(glGetUniformLocation(shaderProgram, info.name), b1, b2, b3);
			break;
		}
		case 4: {
			XelaVec4<void *> *vec4 = (XelaVec4<void *> *)info.data;
			bool b1 = getBool(info.inFormat, vec4->x);
			bool b2 = getBool(info.inFormat, vec4->y);
			bool b3 = getBool(info.inFormat, vec4->z);
			bool b4 = getBool(info.inFormat, vec4->w);
			glUniform4i(glGetUniformLocation(shaderProgram, info.name), b1, b2, b3, b4);
			break;
		}
	}
}
void XelaShader::setIntUniform(XelaUniformInfo info) {
	switch (info.size) {
		case 1: {
			int i = getInt(info.inFormat, info.data);
			glUniform1i(glGetUniformLocation(shaderProgram, info.name), i);
			break;
		}
		case 2: {
			XelaVec2<void *> *vec2 = (XelaVec2<void *> *)info.data;
			int i1 = getInt(info.inFormat, vec2->x);
			int i2 = getInt(info.inFormat, vec2->y);
			glUniform2i(glGetUniformLocation(shaderProgram, info.name), i1, i2);
			break;
		}
		case 3: {
			XelaVec3<void *> *vec3 = (XelaVec3<void *> *)info.data;
			int i1 = getInt(info.inFormat, vec3->x);
			int i2 = getInt(info.inFormat, vec3->y);
			int i3 = getInt(info.inFormat, vec3->z);
			glUniform3i(glGetUniformLocation(shaderProgram, info.name), i1, i2, i3);
			break;
		}
		case 4: {
			XelaVec4<void *> *vec4 = (XelaVec4<void *> *)info.data;
			int i1 = getInt(info.inFormat, vec4->x);
			int i2 = getInt(info.inFormat, vec4->y);
			int i3 = getInt(info.inFormat, vec4->z);
			int i4 = getInt(info.inFormat, vec4->w);
			glUniform4i(glGetUniformLocation(shaderProgram, info.name), i1, i2, i3, i4);
			break;
		}
	}
}
void XelaShader::setUnsignedIntUniform(XelaUniformInfo info) {
	switch (info.size) {
		case 1: {
			unsigned int u = getUnsignedInt(info.inFormat, info.data);
			glUniform1ui(glGetUniformLocation(shaderProgram, info.name), u);
			break;
		}
		case 2: {
			XelaVec2<void *> *vec2 = (XelaVec2<void *> *)info.data;
			unsigned int u1 = getUnsignedInt(info.inFormat, vec2->x);
			unsigned int u2 = getUnsignedInt(info.inFormat, vec2->y);
			glUniform2ui(glGetUniformLocation(shaderProgram, info.name), u1, u2);
			break;
		}
		case 3: {
			XelaVec3<void *> *vec3 = (XelaVec3<void *> *)info.data;
			unsigned int u1 = getUnsignedInt(info.inFormat, vec3->x);
			unsigned int u2 = getUnsignedInt(info.inFormat, vec3->y);
			unsigned int u3 = getUnsignedInt(info.inFormat, vec3->z);
			glUniform3ui(glGetUniformLocation(shaderProgram, info.name), u1, u2, u3);
			break;
		}
		case 4: {
			XelaVec4<void *> *vec4 = (XelaVec4<void *> *)info.data;
			unsigned int u1 = getUnsignedInt(info.inFormat, vec4->x);
			unsigned int u2 = getUnsignedInt(info.inFormat, vec4->y);
			unsigned int u3 = getUnsignedInt(info.inFormat, vec4->z);
			unsigned int u4 = getUnsignedInt(info.inFormat, vec4->w);
			glUniform4ui(glGetUniformLocation(shaderProgram, info.name), u1, u2, u3, u4);
			break;
		}
	}
}
void XelaShader::setFloatUniform(XelaUniformInfo info) {
	switch (info.size) {
		case 1: {
			float f = getFloat(info.inFormat, info.data);
			glUniform1f(glGetUniformLocation(shaderProgram, info.name), f);
			break;
		}
		case 2: {
			XelaVec2<void *> *vec2 = (XelaVec2<void *> *)info.data;
			float f1 = getFloat(info.inFormat, vec2->x);
			float f2 = getFloat(info.inFormat, vec2->y);
			glUniform2f(glGetUniformLocation(shaderProgram, info.name), f1, f2);
			break;
		}
		case 3: {
			XelaVec3<void *> *vec3 = (XelaVec3<void *> *)info.data;
			float f1 = getFloat(info.inFormat, vec3->x);
			float f2 = getFloat(info.inFormat, vec3->y);
			float f3 = getFloat(info.inFormat, vec3->z);
			glUniform3f(glGetUniformLocation(shaderProgram, info.name), f1, f2, f3);
			break;
		}
		case 4: {
			XelaVec4<void *> *vec4 = (XelaVec4<void *> *)info.data;
			float f1 = getFloat(info.inFormat, vec4->x);
			float f2 = getFloat(info.inFormat, vec4->y);
			float f3 = getFloat(info.inFormat, vec4->z);
			float f4 = getFloat(info.inFormat, vec4->w);
			glUniform4f(glGetUniformLocation(shaderProgram, info.name), f1, f2, f3, f4);
			break;
		}
	}
}
void XelaShader::setDoubleUniform(XelaUniformInfo info) {
	switch (info.size) {
		case 1: {
			double d = getDouble(info.inFormat, info.data);
			glUniform1d(glGetUniformLocation(shaderProgram, info.name), d);
			break;
		}
		case 2: {
			XelaVec2<void *> *vec2 = (XelaVec2<void *> *)info.data;
			double d1 = getDouble(info.inFormat, vec2->x);
			double d2 = getDouble(info.inFormat, vec2->y);
			glUniform2d(glGetUniformLocation(shaderProgram, info.name), d1, d2);
			break;
		}
		case 3: {
			XelaVec3<void *> *vec3 = (XelaVec3<void *> *)info.data;
			double d1 = getDouble(info.inFormat, vec3->x);
			double d2 = getDouble(info.inFormat, vec3->y);
			double d3 = getDouble(info.inFormat, vec3->z);
			glUniform3d(glGetUniformLocation(shaderProgram, info.name), d1, d2, d3);
			break;
		}
		case 4: {
			XelaVec4<void *> *vec4 = (XelaVec4<void *> *)info.data;
			double d1 = getDouble(info.inFormat, vec4->x);
			double d2 = getDouble(info.inFormat, vec4->y);
			double d3 = getDouble(info.inFormat, vec4->z);
			double d4 = getDouble(info.inFormat, vec4->w);
			glUniform4d(glGetUniformLocation(shaderProgram, info.name), d1, d2, d3, d4);
			break;
		}
	}
}
void XelaShader::setUniforms() {
	//Set texture uniforms.
	for (int i = 0; i < texList.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, texList[i].id);
		glUniform1i(glGetUniformLocation(shaderProgram, texList[i].name), i);
	}
	//Set other uniforms.
	for (int i = 0; i < uniforms.size(); i++) {
		switch (uniforms[i].outFormat) {
			case XELA_BOOL:
				setBoolUniform(uniforms[i]);
				break;
			case XELA_INT:
				setIntUniform(uniforms[i]);
				break;
			case XELA_UNSIGNED_INT:
				setUnsignedIntUniform(uniforms[i]);
				break;
			case XELA_FLOAT:
				setFloatUniform(uniforms[i]);
				break;
			case XELA_DOUBLE:
				setDoubleUniform(uniforms[i]);
				break;
		}
	}
}
void XelaShader::use() {
	glUseProgram(shaderProgram);
	setUniforms();
	for (int i = 0; i < (int)shaderCB.size(); i++) {
		shaderCB[i](shaderProgram);
	}
}

void XelaShader::addUniform(const char *name, int inType, int outType, void *data) {
	XelaUniformInfo info;
	info.name = name;
	info.size = 1;
	info.inFormat = inType;
	info.outFormat = outType;
	info.data = data;
	uniforms.push_back(info);
}
void XelaShader::addUniformVec2(const char *name, int inType, int outType, void *data1, void *data2) {
	XelaUniformInfo info;
	info.name = name;
	info.size = 2;
	info.inFormat = inType;
	info.outFormat = outType;
	info.data = new XelaVec2<void *>({ data1, data2 });
	uniforms.push_back(info);
}
void XelaShader::addUniformVec3(const char *name, int inType, int outType, void *data1, void *data2, void *data3) {
	XelaUniformInfo info;
	info.name = name;
	info.size = 3;
	info.inFormat = inType;
	info.outFormat = outType;
	info.data = new XelaVec3<void *>({ data1, data2, data3 });
	uniforms.push_back(info);
}
void XelaShader::addUniformVec4(const char *name, int inType, int outType, void *data1, void *data2, void *data3, void *data4) {
	XelaUniformInfo info;
	info.name = name;
	info.size = 4;
	info.inFormat = inType;
	info.outFormat = outType;
	info.data = new XelaVec4<void *>({ data1, data2, data3, data4 });
	uniforms.push_back(info);
}

std::vector<XelaImageInfo> XelaShader::getTexList() {
	return texList;
}
unsigned int XelaShader::getProgram() {
	return shaderProgram;
}