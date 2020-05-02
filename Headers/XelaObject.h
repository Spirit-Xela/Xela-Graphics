#ifndef _XELA_OBJECT_H
#define _XELA_OBJECT_H

//Xela Graphics
#include "XelaGraphics.h"

//C++
#include <vector>

extern "C" {
	struct XelaObject {
		//Info on where data is stored for OpenGL functions
		unsigned int VBO = -1, VAO = -1, EBO = -1;

		//Complete data to send to OpenGL
		std::vector<float> resData;

		//Data for each shader location to be put into resData
		std::vector<XelaVertexData<float>> vertData;

		//Indices of the object
		std::vector<unsigned int> indices;

		//Keeping track of the object's size
		float minX = 0, minY = 0, minZ = 0, maxX = 0, maxY = 0, maxZ = 0;

		//Creates a new XelaObject
		XELAGRAPHICS_API static XelaObject *genObject();

		//Add an index to this object
		XELAGRAPHICS_API static void addIndex(XelaObject *o, XelaVec3<unsigned int> ind);
		//Add multiple indices to this object
		XELAGRAPHICS_API static void addIndices(XelaObject *o, XelaVec3<unsigned int> *inds, int count);

		//Remove all indices from this object
		XELAGRAPHICS_API static void clearIndices(XelaObject *o);
		//Remove all indices from this object and set new ones
		XELAGRAPHICS_API static void setIndices(XelaObject *o, XelaVec3<unsigned int> *inds, int count);

		//Clear vertex data at a specified location
		XELAGRAPHICS_API static void clearVertexData(XelaObject *o, int id);

		//Add float vertex data
		//This data will be sent to location id in the vertex shader
		//If id is already taken by float data, that data will be appended with vec
		//If id is already taken by data of a different length, this function will do nothing
		//id 0 is assumed to be vertices and will be used for size calculations
		XELAGRAPHICS_API static void addVertexDataf(XelaObject *o, float vec, int id);
		//Add float vertex data
		//This data will be sent to location id in the vertex shader
		//If id is already taken by float data, that data will be appended with vec
		//If id is already taken by data of a different length, this function will do nothing
		//id 0 is assumed to be vertices and will be used for size calculations
		XELAGRAPHICS_API static void addVertexDatafv(XelaObject *o, float *vec, int count, int id);

		//Set float vertex data
		//This data will be sent to location id in the vertex shader
		//If id is already taken by float data, vec will replace it
		//If id is already taken by data of a different length, vec will replace it
		//id 0 is assumed to be vertices and will be used for size calculations
		XELAGRAPHICS_API static void setVertexDataf(XelaObject *o, float vec, int id);
		//Set float vertex data
		//This data will be sent to location id in the vertex shader
		//If id is already taken by float data, vec will replace it
		//If id is already taken by data of a different length, vec will replace it
		//id 0 is assumed to be vertices and will be used for size calculations
		XELAGRAPHICS_API static void setVertexDatafv(XelaObject *o, float *vec, int count, int id);

		//Add vec2 vertex data
		//This data will be sent to location id in the vertex shader
		//If id is already taken by vec2 data, that data will be appended with vec
		//If id is already taken by data of a different length, this function will do nothing
		//id 0 is assumed to be vertices and will be used for size calculations
		XELAGRAPHICS_API static void addVertexData2f(XelaObject *o, XelaVec2<float> vec, int id);
		//Add vec2 vertex data
		//This data will be sent to location id in the vertex shader
		//If id is already taken by vec2 data, that data will be appended with vec
		//If id is already taken by data of a different length, this function will do nothing
		//id 0 is assumed to be vertices and will be used for size calculations
		XELAGRAPHICS_API static void addVertexData2fv(XelaObject *o, XelaVec2<float> *vec, int count, int id);

		//Set vec2 vertex data
		//This data will be sent to location id in the vertex shader
		//If id is already taken by vec2 data, vec will replace it
		//If id is already taken by data of a different length, vec will replace it
		//id 0 is assumed to be vertices and will be used for size calculations
		XELAGRAPHICS_API static void setVertexData2f(XelaObject *o, XelaVec2<float> vec, int id);
		//Set vec2 vertex data
		//This data will be sent to location id in the vertex shader
		//If id is already taken by vec2 data, vec will replace it
		//If id is already taken by data of a different length, vec will replace it
		//id 0 is assumed to be vertices and will be used for size calculations
		XELAGRAPHICS_API static void setVertexData2fv(XelaObject *o, XelaVec2<float> *vec, int count, int id);

		//Add vec3 vertex data
		//This data will be sent to location id in the vertex shader
		//If id is already taken by vec3 data, that data will be appended with vec
		//If id is already taken by data of a different length, this function will do nothing
		//id 0 is assumed to be vertices and will be used for size calculations
		XELAGRAPHICS_API static void addVertexData3f(XelaObject *o, XelaVec3<float> vec, int id);
		//Add vec3 vertex data
		//This data will be sent to location id in the vertex shader
		//If id is already taken by vec3 data, that data will be appended with vec
		//If id is already taken by data of a different length, this function will do nothing
		//id 0 is assumed to be vertices and will be used for size calculations
		XELAGRAPHICS_API static void addVertexData3fv(XelaObject *o, XelaVec3<float> *vec, int count, int id);

		//Set vec3 vertex data
		//This data will be sent to location id in the vertex shader
		//If id is already taken by vec3 data, vec will replace it
		//If id is already taken by data of a different length, vec will replace it
		//id 0 is assumed to be vertices and will be used for size calculations
		XELAGRAPHICS_API static void setVertexData3f(XelaObject *o, XelaVec3<float> vec, int id);
		//Set vec3 vertex data
		//This data will be sent to location id in the vertex shader
		//If id is already taken by vec3 data, vec will replace it
		//If id is already taken by data of a different length, vec will replace it
		//id 0 is assumed to be vertices and will be used for size calculations
		XELAGRAPHICS_API static void setVertexData3fv(XelaObject *o, XelaVec3<float> *vec, int count, int id);

		//Add vec4 vertex data
		//This data will be sent to location id in the vertex shader
		//If id is already taken by vec4 data, that data will be appended with vec
		//If id is already taken by data of a different length, this function will do nothing
		//id 0 is assumed to be vertices and will be used for size calculations
		XELAGRAPHICS_API static void addVertexData4f(XelaObject *o, XelaVec4<float> vec, int id);
		//Add vec4 vertex data
		//This data will be sent to location id in the vertex shader
		//If id is already taken by vec4 data, that data will be appended with vec
		//If id is already taken by data of a different length, this function will do nothing
		//id 0 is assumed to be vertices and will be used for size calculations
		XELAGRAPHICS_API static void addVertexData4fv(XelaObject *o, XelaVec4<float> *vec, int count, int id);

		//Set vec4 vertex data
		//This data will be sent to location id in the vertex shader
		//If id is already taken by vec4 data, vec will replace it
		//If id is already taken by data of a different length, vec will replace it
		//id 0 is assumed to be vertices and will be used for size calculations
		XELAGRAPHICS_API static void setVertexData4f(XelaObject *o, XelaVec4<float> vec, int id);
		//Set vec4 vertex data
		//This data will be sent to location id in the vertex shader
		//If id is already taken by vec4 data, vec will replace it
		//If id is already taken by data of a different length, vec will replace it
		//id 0 is assumed to be vertices and will be used for size calculations
		XELAGRAPHICS_API static void setVertexData4fv(XelaObject *o, XelaVec4<float> *vec, int count, int id);

		//Sets the update frequency of this data in the shader
		//0 - update for every vertex
		//1 - update every instance
		//2 - update every 2nd instance
		//3+ ...
		XELAGRAPHICS_API static void setDataUpdateFrequency(XelaObject *o, int id, int freq);

		//Updates all the VAO, VBO, EBO data
		XELAGRAPHICS_API static void updateData(XelaObject *o);

		//Draws the object on screen
		//Count = how many instances to draw
		XELAGRAPHICS_API static void draw(XelaObject *o, unsigned int count);

		//Returns the size of a box drawn around the object
		//x = <Maximum x-coordinate of vertices> - <Minimum x-coordinate of vertices>
		//y = <Maximum y-coordinate of vertices> - <Minimum y-coordinate of vertices>
		//z = <Maximum z-coordinate of vertices> - <Minimum z-coordinate of vertices>
		XELAGRAPHICS_API static XelaVec3<float> getSize(XelaObject *o);
	};
}

#endif