#pragma once

#ifndef STATICMESH3D_H_
#define STATICMESH3D_H_

#include <OpenGL/VertexBufferObject/VertexBufferObject.h>

class StaticMesh3D
{
public:
	static const int POSITION_ATTRIBUTE_INDEX;
	static const int TEXTURE_COORDINATE_ATTRIBUTE_INDEX;
	static const int NORMAL_ATTRIBUTE_INDEX;

	StaticMesh3D(bool withPositions, bool withTextureCoordinates, bool withNormals);
	virtual ~StaticMesh3D();

	virtual void render() const = 0;
	virtual void renderPoints() const {}
	virtual void deleteMesh();
	bool hasPositions() const;
	bool hasTextureCoordinates() const;
	bool hasNormals() const;
	int getVertexByteSize() const;

protected:
	bool _hasPositions = false; 
	bool _hasTextureCoordinates = false;
	bool _hasNormals = false; 

	bool _isInitialized = false; 
	GLuint _vao = 0;
	VertexBufferObject _vbo; 

	virtual void initializeData() {}
	void setVertexAttributesPointers(int numVertices);


};


#endif // !STATICMESH3D_H_
