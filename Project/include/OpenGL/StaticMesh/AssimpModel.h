#pragma once

#ifndef ASSIMPMODEL_H_
#define ASSIMPMODEL_H_

#include <OpenGL/StaticMesh/StaticMesh3D.h>
#include <assimp/Importer.hpp>

class AssimpModel : public StaticMesh3D
{
public:
	AssimpModel(const std::string& filePath, const std::string& defaultTextureName, bool withPositions, bool withTextureCoordinates, bool withNormals, const glm::mat4& modelTransformMatrix = glm::mat4(1.0f));
	AssimpModel(const std::string& filePath, bool withPositions = true, bool withTextureCoordinates = true, bool withNormals = true, const glm::mat4& modelTransformMatrix = glm::mat4(1.0f));

	bool loadModelFromFile(const std::string& filePath, const std::string& defaultTextureName = "", const glm::mat4& modelTransformMatrix = glm::mat4(1.0f));

	void render() const override;
	void renderPoints() const override;

protected:
    void loadMaterialTexture(const int materialIndex, const std::string& textureFileName);
    static std::string aiStringToStdString(const aiString& aiStringStruct);

    string _modelRootDirectoryPath; 
    vector<int> _meshStartIndices; 
    vector<int> _meshVerticesCount; 
    vector<int> _meshMaterialIndices; 
    map<int, string> _materialTextureKeys;
};

#endif // !ASSIMPMODEL_H_
