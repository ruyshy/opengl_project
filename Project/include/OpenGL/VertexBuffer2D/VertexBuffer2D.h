#pragma once

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

class VertexBufferObject2D
{
public:
	unsigned int VAO;  //vertex array object
	unsigned int VBO;  // vertex buffer object
	unsigned int EBO;	// Element Buffer Object
	unsigned int CBO;  // color buffer object
	unsigned int UVBO; // uv buffer object

	void draw();
};

class VertexBufferSystem2D
{
public:
	static const unsigned int indices[];
	static VertexBufferObject2D Generate();
	static void Delete(VertexBufferObject2D& obj);

};

#endif // !RECTANGLE_H_