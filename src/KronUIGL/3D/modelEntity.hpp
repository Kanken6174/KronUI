#pragma once

#include "entity.hpp"
#include <string>

class ModelEntity : public Entity {
public:
    std::string filename;

    ModelEntity(const std::string& filename);

    void loadModel();
};