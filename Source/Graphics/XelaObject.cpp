//Libs
#include "GL/glew.h"

//Xela Graphics
#include "XelaObject.h"

XelaObject *XelaObject::genObject() {
	XelaObject *o = new XelaObject();

	//Generate array/buffers for this object
	glGenVertexArrays(1, &o->VAO);
	glGenBuffers(1, &o->VBO);
	glGenBuffers(1, &o->EBO);

	return o;
}

static void xelaGenObjectResData(XelaObject *o) {
	o->resData.clear();
	for (int i = 0; i < o->vertData.size(); i++) {
		if (o->vertData[i].id == 0) {
			//If id == 0, assume this is a vertex and use it to keep track of the object's size.
			for (int k = 0; k < o->vertData[i].data.size(); k += o->vertData[i].dataSize) {
				if (o->vertData[i].dataSize >= 3) {
					o->maxZ = (o->vertData[i].data[k + 2] > o->maxZ) ? o->vertData[i].data[k] : o->maxZ;
					o->minZ = (o->vertData[i].data[k + 2] < o->minZ) ? o->vertData[i].data[k] : o->minZ;
				}
				if (o->vertData[i].dataSize >= 2) {
					o->maxY = (o->vertData[i].data[k + 1] > o->maxY) ? o->vertData[i].data[k] : o->maxY;
					o->minY = (o->vertData[i].data[k + 1] < o->minY) ? o->vertData[i].data[k] : o->minY;
				}
				if (o->vertData[i].dataSize >= 1) {
					o->maxX = (o->vertData[i].data[k] > o->maxX) ? o->vertData[i].data[k] : o->maxX;
					o->minX = (o->vertData[i].data[k] < o->minX) ? o->vertData[i].data[k] : o->minX;
				}
			}
		}

		//Add to resData
		for (int k = 0; k < o->vertData[i].data.size(); k++) {
			o->resData.push_back(o->vertData[i].data[k]);
		}
	}
}
void XelaObject::updateData(XelaObject *o) {
	//Generate complete data array
	xelaGenObjectResData(o);

	//Bind vertex array and buffer
	glBindVertexArray(o->VAO);

	//Save vertex data to buffer
	glBindBuffer(GL_ARRAY_BUFFER, o->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * o->resData.size(), o->resData.data(), GL_DYNAMIC_DRAW);

	//Save index data to buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, o->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * o->indices.size(), o->indices.data(), GL_DYNAMIC_DRAW);

	//Total offset between indices
	int offset = 0;
	for (int i = 0; i < o->vertData.size(); i++) {
		//Setup vertex attribute at given id
		glVertexAttribPointer(o->vertData[i].id, o->vertData[i].dataSize, GL_FLOAT, GL_FALSE, o->vertData[i].dataSize * sizeof(float), (void *)offset);
		glEnableVertexAttribArray(o->vertData[i].id);
		glVertexAttribDivisor(o->vertData[i].id, o->vertData[i].update);
		//Add attribute's size to offset
		offset += o->vertData[i].data.size() * sizeof(float);
	}

	//Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void XelaObject::addIndex(XelaObject *o, XelaVec3<unsigned int> ind) {
	o->indices.push_back(ind.x);
	o->indices.push_back(ind.y);
	o->indices.push_back(ind.z);
}
void XelaObject::addIndices(XelaObject *o, XelaVec3<unsigned int> *inds, int count) {
	for (int i = 0; i < count; i++) {
		o->indices.push_back(inds[i].x);
		o->indices.push_back(inds[i].y);
		o->indices.push_back(inds[i].z);
	}
}
void XelaObject::clearIndices(XelaObject *o) {
	o->indices.clear();
}
void XelaObject::setIndices(XelaObject *o, XelaVec3<unsigned int> *inds, int count) {
	o->indices.clear();
	for (int i = 0; i < count; i++) {
		o->indices.push_back(inds[i].x);
		o->indices.push_back(inds[i].y);
		o->indices.push_back(inds[i].z);
	}
}


void XelaObject::clearVertexData(XelaObject *o, int id) {
	for (int i = 0; i < o->vertData.size(); i++) {
		if (o->vertData[i].id == id) {
			o->vertData.erase(o->vertData.begin() + i);
			break;
		}
	}
}

void XelaObject::addVertexDataf(XelaObject *o, float vec, int id) {
	bool found = false;
	for (int i = 0; i < o->vertData.size(); i++) {
		if (o->vertData[i].id == id) {
			found = true;
			if (o->vertData[i].dataSize == 1) {
				o->vertData[i].data.push_back(vec);
			}
			break;
		}
	}

	if (!found) {
		o->vertData.push_back({ id, 1, 0, *new std::vector<float> });
		o->vertData[o->vertData.size() - 1].data.push_back(vec);
	}
}
void XelaObject::addVertexDatafv(XelaObject *o, float* vec, int count, int id) {
	bool found = false;
	for (int i = 0; i < o->vertData.size(); i++) {
		if (o->vertData[i].id == id) {
			found = true;
			if (o->vertData[i].dataSize == 1) {
				for (int k = 0; k < count; k++) {
					o->vertData[i].data.push_back(vec[k]);
				}
			}
			break;
		}
	}

	if (!found) {
		o->vertData.push_back({ id, 1, 0, *new std::vector<float> });
		for (int k = 0; k < count; k++) {
			o->vertData[o->vertData.size() - 1].data.push_back(vec[k]);
		}
	}
}
void XelaObject::setVertexDataf(XelaObject *o, float vec, int id) {
	XelaObject::clearVertexData(o, id);
	XelaObject::addVertexDataf(o, vec, id);
}
void XelaObject::setVertexDatafv(XelaObject *o, float* vec, int count, int id) {
	XelaObject::clearVertexData(o, id);
	XelaObject::addVertexDatafv(o, vec, count, id);
}

void XelaObject::addVertexData2f(XelaObject *o, XelaVec2<float> vec, int id) {
	bool found = false;
	for (int i = 0; i < o->vertData.size(); i++) {
		if (o->vertData[i].id == id) {
			found = true;
			if (o->vertData[i].dataSize == 2) {
				o->vertData[i].data.push_back(vec.x);
				o->vertData[i].data.push_back(vec.y);
			}
			break;
		}
	}

	if (!found) {
		o->vertData.push_back({ id, 2, 0, *new std::vector<float> });
		o->vertData[o->vertData.size() - 1].data.push_back(vec.x);
		o->vertData[o->vertData.size() - 1].data.push_back(vec.y);
	}
}
void XelaObject::addVertexData2fv(XelaObject *o, XelaVec2<float>* vec, int count, int id) {
	bool found = false;
	for (int i = 0; i < o->vertData.size(); i++) {
		if (o->vertData[i].id == id) {
			found = true;
			if (o->vertData[i].dataSize == 2) {
				for (int k = 0; k < count; k++) {
					o->vertData[i].data.push_back(vec[k].x);
					o->vertData[i].data.push_back(vec[k].y);
				}
			}
			break;
		}
	}

	if (!found) {
		o->vertData.push_back({ id, 2, 0, *new std::vector<float> });
		for (int k = 0; k < count; k++) {
			o->vertData[o->vertData.size() - 1].data.push_back(vec[k].x);
			o->vertData[o->vertData.size() - 1].data.push_back(vec[k].y);
		}
	}
}
void XelaObject::setVertexData2f(XelaObject *o, XelaVec2<float> vec, int id) {
	XelaObject::clearVertexData(o, id);
	XelaObject::addVertexData2f(o, vec, id);
}
void XelaObject::setVertexData2fv(XelaObject *o, XelaVec2<float>* vec, int count, int id) {
	XelaObject::clearVertexData(o, id);
	XelaObject::addVertexData2fv(o, vec, count, id);
}

void XelaObject::addVertexData3f(XelaObject *o, XelaVec3<float> vec, int id) {
	bool found = false;
	for (int i = 0; i < o->vertData.size(); i++) {
		if (o->vertData[i].id == id) {
			found = true;
			if (o->vertData[i].dataSize == 3) {
				o->vertData[i].data.push_back(vec.x);
				o->vertData[i].data.push_back(vec.y);
				o->vertData[i].data.push_back(vec.z);
			}
			break;
		}
	}

	if (!found) {
		o->vertData.push_back({ id, 3, 0, *new std::vector<float> });
		o->vertData[o->vertData.size() - 1].data.push_back(vec.x);
		o->vertData[o->vertData.size() - 1].data.push_back(vec.y);
		o->vertData[o->vertData.size() - 1].data.push_back(vec.z);
	}
}
void XelaObject::addVertexData3fv(XelaObject *o, XelaVec3<float>* vec, int count, int id) {
	bool found = false;
	for (int i = 0; i < o->vertData.size(); i++) {
		if (o->vertData[i].id == id) {
			found = true;
			if (o->vertData[i].dataSize == 3) {
				for (int k = 0; k < count; k++) {
					o->vertData[i].data.push_back(vec[k].x);
					o->vertData[i].data.push_back(vec[k].y);
					o->vertData[i].data.push_back(vec[k].z);
				}
			}
			break;
		}
	}

	if (!found) {
		o->vertData.push_back({ id, 3, 0, *new std::vector<float> });
		for (int k = 0; k < count; k++) {
			o->vertData[o->vertData.size() - 1].data.push_back(vec[k].x);
			o->vertData[o->vertData.size() - 1].data.push_back(vec[k].y);
			o->vertData[o->vertData.size() - 1].data.push_back(vec[k].z);
		}
	}
}
void XelaObject::setVertexData3f(XelaObject *o, XelaVec3<float> vec, int id) {
	XelaObject::clearVertexData(o, id);
	XelaObject::addVertexData3f(o, vec, id);
}
void XelaObject::setVertexData3fv(XelaObject *o, XelaVec3<float>* vec, int count, int id) {
	XelaObject::clearVertexData(o, id);
	XelaObject::addVertexData3fv(o, vec, count, id);
}

void XelaObject::addVertexData4f(XelaObject *o, XelaVec4<float> vec, int id) {
	bool found = false;
	for (int i = 0; i < o->vertData.size(); i++) {
		if (o->vertData[i].id == id) {
			found = true;
			if (o->vertData[i].dataSize == 4) {
				o->vertData[i].data.push_back(vec.x);
				o->vertData[i].data.push_back(vec.y);
				o->vertData[i].data.push_back(vec.z);
				o->vertData[i].data.push_back(vec.w);
			}
			break;
		}
	}

	if (!found) {
		o->vertData.push_back({ id, 4, 0, *new std::vector<float> });
		o->vertData[o->vertData.size() - 1].data.push_back(vec.x);
		o->vertData[o->vertData.size() - 1].data.push_back(vec.y);
		o->vertData[o->vertData.size() - 1].data.push_back(vec.z);
		o->vertData[o->vertData.size() - 1].data.push_back(vec.w);
	}
}
void XelaObject::addVertexData4fv(XelaObject *o, XelaVec4<float>* vec, int count, int id) {
	bool found = false;
	for (int i = 0; i < o->vertData.size(); i++) {
		if (o->vertData[i].id == id) {
			found = true;
			if (o->vertData[i].dataSize == 4) {
				for (int k = 0; k < count; k++) {
					o->vertData[i].data.push_back(vec[k].x);
					o->vertData[i].data.push_back(vec[k].y);
					o->vertData[i].data.push_back(vec[k].z);
					o->vertData[i].data.push_back(vec[k].w);
				}
			}
			break;
		}
	}

	if (!found) {
		o->vertData.push_back({ id, 4, 0, *new std::vector<float> });
		for (int k = 0; k < count; k++) {
			o->vertData[o->vertData.size() - 1].data.push_back(vec[k].x);
			o->vertData[o->vertData.size() - 1].data.push_back(vec[k].y);
			o->vertData[o->vertData.size() - 1].data.push_back(vec[k].z);
			o->vertData[o->vertData.size() - 1].data.push_back(vec[k].w);
		}
	}
}
void XelaObject::setVertexData4f(XelaObject *o, XelaVec4<float> vec, int id) {
	XelaObject::clearVertexData(o, id);
	XelaObject::addVertexData4f(o, vec, id);
}
void XelaObject::setVertexData4fv(XelaObject *o, XelaVec4<float>* vec, int count, int id) {
	XelaObject::clearVertexData(o, id);
	XelaObject::addVertexData4fv(o, vec, count, id);
}

void XelaObject::setDataUpdateFrequency(XelaObject *o, int id, int freq) {
	for (int i = 0; i < o->vertData.size(); i++) {
		if (o->vertData[i].id == id) {
			o->vertData[i].update = freq;
			break;
		}
	}
}

void XelaObject::draw(XelaObject *o, unsigned int count) {
	glBindVertexArray(o->VAO);
	glDrawElementsInstanced(GL_TRIANGLES, o->indices.size(), GL_UNSIGNED_INT, 0, count);
	glBindVertexArray(0);
}

XelaVec3<float> XelaObject::getSize(XelaObject *o) {
	return { o->maxX - o->minX, o->maxY - o->minY, o->maxZ - o->minZ };
}