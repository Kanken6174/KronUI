#include "modelEntity.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

ModelEntity::ModelEntity(const std::string& filename) : Entity(0.0f, 0.0f, 0.0f), filename(filename) {}

void ModelEntity::loadModel() {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    // Process the scene's root node recursively
    // processNode(scene->mRootNode, scene);
}