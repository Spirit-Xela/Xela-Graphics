#include "XelaObject.h"

XelaObject::XelaObject() {
	//Generate array/buffers for this object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

void XelaObject::genResData() {
	resData.clear();
	for (int i = 0; i < vertData.size(); i++) {
		if (vertData[i].id == 0) {
			//If id == 0, assume this is a vertex and use it to keep track of the object's size.
			for (int k = 0; k < vertData[i].data.size(); k += vertData[i].dataSize) {
				if (vertData[i].dataSize >= 3) {
					maxZ = (vertData[i].data[k + 2] > maxZ) ? vertData[i].data[k] : maxZ;
					minZ = (vertData[i].data[k + 2] < minZ) ? vertData[i].data[k] : minZ;
				}
				if (vertData[i].dataSize >= 2) {
					maxY = (vertData[i].data[k + 1] > maxY) ? vertData[i].data[k] : maxY;
					minY = (vertData[i].data[k + 1] < minY) ? vertData[i].data[k] : minY;
				}
				if (vertData[i].dataSize >= 1) {
					maxX = (vertData[i].data[k] > maxX) ? vertData[i].data[k] : maxX;
					minX = (vertData[i].data[k] < minX) ? vertData[i].data[k] : minX;
				}
			}
		}

		//Add to resData
		for (int k = 0; k < vertData[i].data.size(); k++) {
			resData.push_back(vertData[i].data[k]);
		}
	}
}
void XelaObject::updateData() {
	//Generate complete data array
	genResData();

	//Bind vertex array and buffer
	glBindVertexArray(VAO);

	//Save vertex data to buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * resData.size(), resData.data(), GL_DYNAMIC_DRAW);

	//Save index data to buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_DYNAMIC_DRAW);

	//Total offset between indices
	int offset = 0;
	for (int i = 0; i < vertData.size(); i++) {
		//Setup vertex attribute at given id
		glVertexAttribPointer(vertData[i].id, vertData[i].dataSize, GL_FLOAT, GL_FALSE, vertData[i].dataSize * sizeof(float), (void *)offset);
		glEnableVertexAttribArray(vertData[i].id);
		glVertexAttribDivisor(vertData[i].id, vertData[i].update);
		//Add attribute's size to offset
		offset += vertData[i].data.size() * sizeof(float);
	}

	//Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void XelaObject::addIndex(XelaVec3<unsigned int> ind) {
	indices.push_back(ind.x);
	indices.push_back(ind.y);
	indices.push_back(ind.z);
}
void XelaObject::addIndices(std::vector<XelaVec3<unsigned int>> inds) {
	for (int i = 0; i < inds.size(); i++) {
		indices.push_back(inds[i].x);
		indices.push_back(inds[i].y);
		indices.push_back(inds[i].z);
	}
}
void XelaObject::addIndices(XelaVec3<unsigned int> *inds, int count) {
	for (int i = 0; i < count; i++) {
		indices.push_back(inds[i].x);
		indices.push_back(inds[i].y);
		indices.push_back(inds[i].z);
	}
}
void XelaObject::clearIndices() {
	indices.clear();
}
void XelaObject::setIndices(std::vector<XelaVec3<unsigned int>> inds) {
	indices.clear();
	for (int i = 0; i < inds.size(); i++) {
		indices.push_back(inds[i].x);
		indices.push_back(inds[i].y);
		indices.push_back(inds[i].z);
	}
}
void XelaObject::setIndices(XelaVec3<unsigned int> *inds, int count) {
	indices.clear();
	for (int i = 0; i < count; i++) {
		indices.push_back(inds[i].x);
		indices.push_back(inds[i].y);
		indices.push_back(inds[i].z);
	}
}


void XelaObject::clearVertexData(int id) {
	for (int i = 0; i < vertData.size(); i++) {
		if (vertData[i].id == id) {
			vertData.erase(vertData.begin() + i);
			break;
		}
	}
}

void XelaObject::addVertexData(float vec, int id) {
	bool found = false;
	for (int i = 0; i < vertData.size(); i++) {
		if (vertData[i].id == id) {
			found = true;
			if (vertData[i].dataSize == 1) {
				vertData[i].data.push_back(vec);
			}
			break;
		}
	}

	if (!found) {
		vertData.push_back({ id, 1, 0, *new std::vector<float> });
		vertData[vertData.size() - 1].data.push_back(vec);
	}
}
void XelaObject::addVertexData(std::vector<float> vec, int id) {
	bool found = false;
	for (int i = 0; i < vertData.size(); i++) {
		if (vertData[i].id == id) {
			found = true;
			if (vertData[i].dataSize == 1) {
				for (int k = 0; k < vec.size(); k++) {
					vertData[i].data.push_back(vec[k]);
				}
			}
			break;
		}
	}

	if (!found) {
		vertData.push_back({ id, 1, 0, *new std::vector<float> });
		for (int k = 0; k < vec.size(); k++) {
			vertData[vertData.size() - 1].data.push_back(vec[k]);
		}
	}
}
void XelaObject::addVertexData(float* vec, int count, int id) {
	bool found = false;
	for (int i = 0; i < vertData.size(); i++) {
		if (vertData[i].id == id) {
			found = true;
			if (vertData[i].dataSize == 1) {
				for (int k = 0; k < count; k++) {
					vertData[i].data.push_back(vec[k]);
				}
			}
			break;
		}
	}

	if (!found) {
		vertData.push_back({ id, 1, 0, *new std::vector<float> });
		for (int k = 0; k < count; k++) {
			vertData[vertData.size() - 1].data.push_back(vec[k]);
		}
	}
}
void XelaObject::setVertexData(float vec, int id) {
	clearVertexData(id);
	addVertexData(vec, id);
}
void XelaObject::setVertexData(std::vector<float> vec, int id) {
	clearVertexData(id);
	addVertexData(vec, id);
}
void XelaObject::setVertexData(float* vec, int count, int id) {
	clearVertexData(id);
	addVertexData(vec, count, id);
}

void XelaObject::addVertexData(XelaVec2<float> vec, int id) {
	bool found = false;
	for (int i = 0; i < vertData.size(); i++) {
		if (vertData[i].id == id) {
			found = true;
			if (vertData[i].dataSize == 2) {
				vertData[i].data.push_back(vec.x);
				vertData[i].data.push_back(vec.y);
			}
			break;
		}
	}

	if (!found) {
		vertData.push_back({ id, 2, 0, *new std::vector<float> });
		vertData[vertData.size() - 1].data.push_back(vec.x);
		vertData[vertData.size() - 1].data.push_back(vec.y);
	}
}
void XelaObject::addVertexData(std::vector<XelaVec2<float>> vec, int id) {
	bool found = false;
	for (int i = 0; i < vertData.size(); i++) {
		if (vertData[i].id == id) {
			found = true;
			if (vertData[i].dataSize == 2) {
				for (int k = 0; k < vec.size(); k++) {
					vertData[i].data.push_back(vec[k].x);
					vertData[i].data.push_back(vec[k].y);
				}
			}
			break;
		}
	}

	if (!found) {
		vertData.push_back({ id, 2, 0, *new std::vector<float> });
		for (int k = 0; k < vec.size(); k++) {
			vertData[vertData.size() - 1].data.push_back(vec[k].x);
			vertData[vertData.size() - 1].data.push_back(vec[k].y);
		}
	}
}
void XelaObject::addVertexData(XelaVec2<float>* vec, int count, int id) {
	bool found = false;
	for (int i = 0; i < vertData.size(); i++) {
		if (vertData[i].id == id) {
			found = true;
			if (vertData[i].dataSize == 2) {
				for (int k = 0; k < count; k++) {
					vertData[i].data.push_back(vec[k].x);
					vertData[i].data.push_back(vec[k].y);
				}
			}
			break;
		}
	}

	if (!found) {
		vertData.push_back({ id, 2, 0, *new std::vector<float> });
		for (int k = 0; k < count; k++) {
			vertData[vertData.size() - 1].data.push_back(vec[k].x);
			vertData[vertData.size() - 1].data.push_back(vec[k].y);
		}
	}
}
void XelaObject::setVertexData(XelaVec2<float> vec, int id) {
	clearVertexData(id);
	addVertexData(vec, id);
}
void XelaObject::setVertexData(std::vector<XelaVec2<float>> vec, int id) {
	clearVertexData(id);
	addVertexData(vec, id);
}
void XelaObject::setVertexData(XelaVec2<float>* vec, int count, int id) {
	clearVertexData(id);
	addVertexData(vec, count, id);
}

void XelaObject::addVertexData(XelaVec3<float> vec, int id) {
	bool found = false;
	for (int i = 0; i < vertData.size(); i++) {
		if (vertData[i].id == id) {
			found = true;
			if (vertData[i].dataSize == 3) {
				vertData[i].data.push_back(vec.x);
				vertData[i].data.push_back(vec.y);
				vertData[i].data.push_back(vec.z);
			}
			break;
		}
	}

	if (!found) {
		vertData.push_back({ id, 3, 0, *new std::vector<float> });
		vertData[vertData.size() - 1].data.push_back(vec.x);
		vertData[vertData.size() - 1].data.push_back(vec.y);
		vertData[vertData.size() - 1].data.push_back(vec.z);
	}
}
void XelaObject::addVertexData(std::vector<XelaVec3<float>> vec, int id) {
	bool found = false;
	for (int i = 0; i < vertData.size(); i++) {
		if (vertData[i].id == id) {
			found = true;
			if (vertData[i].dataSize == 3) {
				for (int k = 0; k < vec.size(); k++) {
					vertData[i].data.push_back(vec[k].x);
					vertData[i].data.push_back(vec[k].y);
					vertData[i].data.push_back(vec[k].z);
				}
			}
			break;
		}
	}

	if (!found) {
		vertData.push_back({ id, 3, 0, *new std::vector<float> });
		for (int k = 0; k < vec.size(); k++) {
			vertData[vertData.size() - 1].data.push_back(vec[k].x);
			vertData[vertData.size() - 1].data.push_back(vec[k].y);
			vertData[vertData.size() - 1].data.push_back(vec[k].z);
		}
	}
}
void XelaObject::addVertexData(XelaVec3<float>* vec, int count, int id) {
	bool found = false;
	for (int i = 0; i < vertData.size(); i++) {
		if (vertData[i].id == id) {
			found = true;
			if (vertData[i].dataSize == 3) {
				for (int k = 0; k < count; k++) {
					vertData[i].data.push_back(vec[k].x);
					vertData[i].data.push_back(vec[k].y);
					vertData[i].data.push_back(vec[k].z);
				}
			}
			break;
		}
	}

	if (!found) {
		vertData.push_back({ id, 3, 0, *new std::vector<float> });
		for (int k = 0; k < count; k++) {
			vertData[vertData.size() - 1].data.push_back(vec[k].x);
			vertData[vertData.size() - 1].data.push_back(vec[k].y);
			vertData[vertData.size() - 1].data.push_back(vec[k].z);
		}
	}
}
void XelaObject::setVertexData(XelaVec3<float> vec, int id) {
	clearVertexData(id);
	addVertexData(vec, id);
}
void XelaObject::setVertexData(std::vector<XelaVec3<float>> vec, int id) {
	clearVertexData(id);
	addVertexData(vec, id);
}
void XelaObject::setVertexData(XelaVec3<float>* vec, int count, int id) {
	clearVertexData(id);
	addVertexData(vec, count, id);
}

void XelaObject::addVertexData(XelaVec4<float> vec, int id) {
	bool found = false;
	for (int i = 0; i < vertData.size(); i++) {
		if (vertData[i].id == id) {
			found = true;
			if (vertData[i].dataSize == 4) {
				vertData[i].data.push_back(vec.x);
				vertData[i].data.push_back(vec.y);
				vertData[i].data.push_back(vec.z);
				vertData[i].data.push_back(vec.w);
			}
			break;
		}
	}

	if (!found) {
		vertData.push_back({ id, 4, 0, *new std::vector<float> });
		vertData[vertData.size() - 1].data.push_back(vec.x);
		vertData[vertData.size() - 1].data.push_back(vec.y);
		vertData[vertData.size() - 1].data.push_back(vec.z);
		vertData[vertData.size() - 1].data.push_back(vec.w);
	}
}
void XelaObject::addVertexData(std::vector<XelaVec4<float>> vec, int id) {
	bool found = false;
	for (int i = 0; i < vertData.size(); i++) {
		if (vertData[i].id == id) {
			found = true;
			if (vertData[i].dataSize == 4) {
				for (int k = 0; k < vec.size(); k++) {
					vertData[i].data.push_back(vec[k].x);
					vertData[i].data.push_back(vec[k].y);
					vertData[i].data.push_back(vec[k].z);
					vertData[i].data.push_back(vec[k].w);
				}
			}
			break;
		}
	}

	if (!found) {
		vertData.push_back({ id, 4, 0, *new std::vector<float> });
		for (int k = 0; k < vec.size(); k++) {
			vertData[vertData.size() - 1].data.push_back(vec[k].x);
			vertData[vertData.size() - 1].data.push_back(vec[k].y);
			vertData[vertData.size() - 1].data.push_back(vec[k].z);
			vertData[vertData.size() - 1].data.push_back(vec[k].w);
		}
	}
}
void XelaObject::addVertexData(XelaVec4<float>* vec, int count, int id) {
	bool found = false;
	for (int i = 0; i < vertData.size(); i++) {
		if (vertData[i].id == id) {
			found = true;
			if (vertData[i].dataSize == 4) {
				for (int k = 0; k < count; k++) {
					vertData[i].data.push_back(vec[k].x);
					vertData[i].data.push_back(vec[k].y);
					vertData[i].data.push_back(vec[k].z);
					vertData[i].data.push_back(vec[k].w);
				}
			}
			break;
		}
	}

	if (!found) {
		vertData.push_back({ id, 4, 0, *new std::vector<float> });
		for (int k = 0; k < count; k++) {
			vertData[vertData.size() - 1].data.push_back(vec[k].x);
			vertData[vertData.size() - 1].data.push_back(vec[k].y);
			vertData[vertData.size() - 1].data.push_back(vec[k].z);
			vertData[vertData.size() - 1].data.push_back(vec[k].w);
		}
	}
}
void XelaObject::setVertexData(XelaVec4<float> vec, int id) {
	clearVertexData(id);
	addVertexData(vec, id);
}
void XelaObject::setVertexData(std::vector<XelaVec4<float>> vec, int id) {
	clearVertexData(id);
	addVertexData(vec, id);
}
void XelaObject::setVertexData(XelaVec4<float>* vec, int count, int id) {
	clearVertexData(id);
	addVertexData(vec, count, id);
}

void XelaObject::setDataUpdateFrequency(int id, int freq) {
	for (int i = 0; i < vertData.size(); i++) {
		if (vertData[i].id == id) {
			vertData[i].update = freq;
			break;
		}
	}
}

void XelaObject::draw(unsigned int count) {
	glBindVertexArray(VAO);
	glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, count);
	glBindVertexArray(0);
}

XelaVec3<float> XelaObject::getSize() {
	return { maxX - minX, maxY - minY, maxZ - minZ };
}