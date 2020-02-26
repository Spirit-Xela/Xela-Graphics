#ifndef _XELA_OBJECT_H
#define _XELA_OBJECT_H

//C++
#include <vector>
#include <iostream>
//Libs
#include "GL/glew.h"
//Engine
#include "XelaDefinitions.h"

class XelaObject {
private:
	//Info on where data is stored for OpenGL functions
	unsigned int VBO = -1, VAO = -1, EBO = -1;

	//Complete data to send to OpenGL
	std::vector<float> resData;

	//Data for each shader location to be put into resData
	std::vector<VertexData<float>> vertData;

	//Indices of the object
	std::vector<unsigned int> indices;

	//Keeping track of the object's size
	float minX = 0, minY = 0, minZ = 0, maxX = 0, maxY = 0, maxZ = 0;

	//Generates the resData vector
	void genResData();
public:
	//Creates a new XelaObject
	XelaObject();

	//Add an index to this object
	void addIndex(XelaVec3<unsigned int> ind);
	//Add multiple indices to this object
	void addIndices(std::vector<XelaVec3<unsigned int>> inds);
	//Add multiple indices to this object
	void addIndices(XelaVec3<unsigned int> *inds, int count);

	//Remove all indices from this object
	void clearIndices();
	//Remove all indices from this object and set new ones
	void setIndices(std::vector<XelaVec3<unsigned int>> inds);
	//Remove all indices from this object and set new ones
	void setIndices(XelaVec3<unsigned int> *inds, int count);

	//Clear vertex data at a specified location
	void clearVertexData(int id);

	//Add float vertex data
	//This data will be sent to location id in the vertex shader
	//If id is already taken by float data, that data will be appended with vec
	//If id is already taken by data of a different length, this function will do nothing
	//id 0 is assumed to be vertices and will be used for size calculations
	void addVertexData(float vec, int id);
	//Add float vertex data
	//This data will be sent to location id in the vertex shader
	//If id is already taken by float data, that data will be appended with vec
	//If id is already taken by data of a different length, this function will do nothing
	//id 0 is assumed to be vertices and will be used for size calculations
	void addVertexData(std::vector<float> vec, int id);
	//Add float vertex data
	//This data will be sent to location id in the vertex shader
	//If id is already taken by float data, that data will be appended with vec
	//If id is already taken by data of a different length, this function will do nothing
	//id 0 is assumed to be vertices and will be used for size calculations
	void addVertexData(float *vec, int count, int id);

	//Set float vertex data
	//This data will be sent to location id in the vertex shader
	//If id is already taken by float data, vec will replace it
	//If id is already taken by data of a different length, vec will replace it
	//id 0 is assumed to be vertices and will be used for size calculations
	void setVertexData(float vec, int id);
	//Set float vertex data
	//This data will be sent to location id in the vertex shader
	//If id is already taken by float data, vec will replace it
	//If id is already taken by data of a different length, vec will replace it
	//id 0 is assumed to be vertices and will be used for size calculations
	void setVertexData(std::vector<float> vec, int id);
	//Set float vertex data
	//This data will be sent to location id in the vertex shader
	//If id is already taken by float data, vec will replace it
	//If id is already taken by data of a different length, vec will replace it
	//id 0 is assumed to be vertices and will be used for size calculations
	void setVertexData(float *vec, int count, int id);

	//Add vec2 vertex data
	//This data will be sent to location id in the vertex shader
	//If id is already taken by vec2 data, that data will be appended with vec
	//If id is already taken by data of a different length, this function will do nothing
	//id 0 is assumed to be vertices and will be used for size calculations
	void addVertexData(XelaVec2<float> vec, int id);
	//Add vec2 vertex data
	//This data will be sent to location id in the vertex shader
	//If id is already taken by vec2 data, that data will be appended with vec
	//If id is already taken by data of a different length, this function will do nothing
	//id 0 is assumed to be vertices and will be used for size calculations
	void addVertexData(std::vector<XelaVec2<float>> vec, int id);
	//Add vec2 vertex data
	//This data will be sent to location id in the vertex shader
	//If id is already taken by vec2 data, that data will be appended with vec
	//If id is already taken by data of a different length, this function will do nothing
	//id 0 is assumed to be vertices and will be used for size calculations
	void addVertexData(XelaVec2<float>* vec, int count, int id);

	//Set vec2 vertex data
	//This data will be sent to location id in the vertex shader
	//If id is already taken by vec2 data, vec will replace it
	//If id is already taken by data of a different length, vec will replace it
	//id 0 is assumed to be vertices and will be used for size calculations
	void setVertexData(XelaVec2<float> vec, int id);
	//Set vec2 vertex data
	//This data will be sent to location id in the vertex shader
	//If id is already taken by vec2 data, vec will replace it
	//If id is already taken by data of a different length, vec will replace it
	//id 0 is assumed to be vertices and will be used for size calculations
	void setVertexData(std::vector<XelaVec2<float>> vec, int id);
	//Set vec2 vertex data
	//This data will be sent to location id in the vertex shader
	//If id is already taken by vec2 data, vec will replace it
	//If id is already taken by data of a different length, vec will replace it
	//id 0 is assumed to be vertices and will be used for size calculations
	void setVertexData(XelaVec2<float>* vec, int count, int id);

	//Add vec3 vertex data
	//This data will be sent to location id in the vertex shader
	//If id is already taken by vec3 data, that data will be appended with vec
	//If id is already taken by data of a different length, this function will do nothing
	//id 0 is assumed to be vertices and will be used for size calculations
	void addVertexData(XelaVec3<float> vec, int id);
	//Add vec3 vertex data
	//This data will be sent to location id in the vertex shader
	//If id is already taken by vec3 data, that data will be appended with vec
	//If id is already taken by data of a different length, this function will do nothing
	//id 0 is assumed to be vertices and will be used for size calculations
	void addVertexData(std::vector<XelaVec3<float>> vec, int id);
	//Add vec3 vertex data
	//This data will be sent to location id in the vertex shader
	//If id is already taken by vec3 data, that data will be appended with vec
	//If id is already taken by data of a different length, this function will do nothing
	//id 0 is assumed to be vertices and will be used for size calculations
	void addVertexData(XelaVec3<float>* vec, int count, int id);

	//Set vec3 vertex data
	//This data will be sent to location id in the vertex shader
	//If id is already taken by vec3 data, vec will replace it
	//If id is already taken by data of a different length, vec will replace it
	//id 0 is assumed to be vertices and will be used for size calculations
	void setVertexData(XelaVec3<float> vec, int id);
	//Set vec3 vertex data
	//This data will be sent to location id in the vertex shader
	//If id is already taken by vec3 data, vec will replace it
	//If id is already taken by data of a different length, vec will replace it
	//id 0 is assumed to be vertices and will be used for size calculations
	void setVertexData(std::vector<XelaVec3<float>> vec, int id);
	//Set vec3 vertex data
	//This data will be sent to location id in the vertex shader
	//If id is already taken by vec3 data, vec will replace it
	//If id is already taken by data of a different length, vec will replace it
	//id 0 is assumed to be vertices and will be used for size calculations
	void setVertexData(XelaVec3<float>* vec, int count, int id);

	//Add vec4 vertex data
	//This data will be sent to location id in the vertex shader
	//If id is already taken by vec4 data, that data will be appended with vec
	//If id is already taken by data of a different length, this function will do nothing
	//id 0 is assumed to be vertices and will be used for size calculations
	void addVertexData(XelaVec4<float> vec, int id);
	//Add vec4 vertex data
	//This data will be sent to location id in the vertex shader
	//If id is already taken by vec4 data, that data will be appended with vec
	//If id is already taken by data of a different length, this function will do nothing
	//id 0 is assumed to be vertices and will be used for size calculations
	void addVertexData(std::vector<XelaVec4<float>> vec, int id);
	//Add vec4 vertex data
	//This data will be sent to location id in the vertex shader
	//If id is already taken by vec4 data, that data will be appended with vec
	//If id is already taken by data of a different length, this function will do nothing
	//id 0 is assumed to be vertices and will be used for size calculations
	void addVertexData(XelaVec4<float>* vec, int count, int id);

	//Set vec4 vertex data
	//This data will be sent to location id in the vertex shader
	//If id is already taken by vec4 data, vec will replace it
	//If id is already taken by data of a different length, vec will replace it
	//id 0 is assumed to be vertices and will be used for size calculations
	void setVertexData(XelaVec4<float> vec, int id);
	//Set vec4 vertex data
	//This data will be sent to location id in the vertex shader
	//If id is already taken by vec4 data, vec will replace it
	//If id is already taken by data of a different length, vec will replace it
	//id 0 is assumed to be vertices and will be used for size calculations
	void setVertexData(std::vector<XelaVec4<float>> vec, int id);
	//Set vec4 vertex data
	//This data will be sent to location id in the vertex shader
	//If id is already taken by vec4 data, vec will replace it
	//If id is already taken by data of a different length, vec will replace it
	//id 0 is assumed to be vertices and will be used for size calculations
	void setVertexData(XelaVec4<float>* vec, int count, int id);

	//Sets the update frequency of this data in the shader
	//0 - update for every vertex
	//1 - update every instance
	//2 - update every 2nd instance
	//3+ ...
	void setDataUpdateFrequency(int id, int freq);

	//Updates all the VAO, VBO, EBO data
	void updateData();

	//Draws the object on screen
	//Count = how many instances to draw
	void draw(unsigned int count);

	//Returns the size of a box drawn around the object
	//x = <Maximum x-coordinate of vertices> - <Minimum x-coordinate of vertices>
	//y = <Maximum y-coordinate of vertices> - <Minimum y-coordinate of vertices>
	//z = <Maximum z-coordinate of vertices> - <Minimum z-coordinate of vertices>
	XelaVec3<float> getSize();
};

#endif