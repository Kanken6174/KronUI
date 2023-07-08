#pragma once
#include <assimp/scene.h>

struct Texture {
    unsigned int id;
    std::vector<float> textureCoordinates;
    std::string type;
    aiString path;
};