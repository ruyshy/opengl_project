#pragma once

#ifndef MODEL3D_H_
#define MODEL3D_H_

#include <OpenGL/Model3D/Mesh.h>

#include <utill/stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class Model3D
{
public:
	Model3D(string const& path, bool gamma = false);
private:
	vector<MeshData::Texture> textures_loaded;
	vector<Mesh>    meshes;
	string directory;
	bool gammaCorrection;
public:
	void Draw(Shader& shader);

private:
	unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

	void loadModel3D(string const& path);

	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	void processNode(aiNode* node, const aiScene* scene);

	vector<MeshData::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
public:

};

#endif // !MODEL3D_H_
