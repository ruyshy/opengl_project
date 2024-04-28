#pragma once

#ifndef MODEL_H_
#define MODEL_H_

#include <OpenGL/Mesh/Mesh.h>

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

class Model
{
public:
    vector<Texture> textures_loaded;
    vector<Mesh>    meshes;
    string directory;
    bool gammaCorrection;

    Model(string const& path, bool gamma = false);

    void Draw(Shader& shader);

private:
    void loadModel(string const& path);

    void processNode(aiNode* node, const aiScene* scene);

    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};


unsigned int TextureFromFile(const char* path, const string& directory, bool gamma);


#endif // !MODEL_H_
