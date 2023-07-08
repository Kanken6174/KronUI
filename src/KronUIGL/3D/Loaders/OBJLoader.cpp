#include "./OBJLoader.hpp"
#include <iostream>
#include <memory>

std::vector<std::shared_ptr<Mesh>> OBJLoader::processNode(aiNode* node, const aiScene* scene) {
    std::vector<std::shared_ptr<Mesh>> meshes;
    for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; ++i) {
        auto childMeshes = processNode(node->mChildren[i], scene);
        meshes.insert(meshes.end(), childMeshes.begin(), childMeshes.end());
    }
    return meshes;
}

std::vector<std::shared_ptr<Mesh>> OBJLoader::loadModel(const std::string& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return {};
    }
    return processNode(scene->mRootNode, scene);
}

std::shared_ptr<Mesh> OBJLoader::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    Transform transform;

    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vertex;
        vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        if (mesh->HasTextureCoords(0))
            vertex.TexCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        vertices.push_back(vertex);
    }
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j)
            indices.push_back(face.mIndices[j]);
    }

    return std::make_shared<Mesh>(vertices, indices, textures, transform);
}