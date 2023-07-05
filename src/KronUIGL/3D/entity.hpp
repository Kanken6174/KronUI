#pragma once

#include <glm/glm.hpp>

class Entity {
public:
    glm::vec3 position;
    glm::vec3 rotation;

    Entity() : position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f) {}

    Entity(float x, float y, float z) : position(x, y, z), rotation(0.0f, 0.0f, 0.0f) {}
};