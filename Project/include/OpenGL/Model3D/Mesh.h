#pragma once
#ifndef MESH_H_
#define MESH_H_

namespace MeshData
{
#define MAX_BONE_INFLUENCE 4

    struct Vertex {
        vec3 Position;
        vec3 Normal;
        vec2 TexCoords;
        vec3 Tangent;
        vec3 Bitangent;
        int m_BoneIDs[MAX_BONE_INFLUENCE];
        float m_Weights[MAX_BONE_INFLUENCE];
    };
    struct Texture {
        unsigned int id;
        string type;
        string path;
    };

};

class Mesh 
{
public:
    Mesh(vector<MeshData::Vertex> vertices, vector<unsigned int> indices, vector<MeshData::Texture> textures);
    
    void Draw(Shader& shader);

public:
    vector<MeshData::Vertex>       vertices;
    vector<unsigned int> indices;
    vector<MeshData::Texture>      textures;

private:
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};

#endif // !MESH_H_
