#pragma once
#include <glm/glm.hpp>

struct Transform {
    glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
    glm::vec3 Rotation  = { 0.0f, 0.0f, 0.0f };
    glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

    glm::mat4 modelMatrix = glm::mat4(1.0f);

    Transform() {}
    Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : Position(position), Rotation(rotation), Scale(scale) {}
    Transform(float x, float y, float z) : Position(x, y, z), Rotation(0.0f, 0.0f, 0.0f), Scale(1.0f, 1.0f, 1.0f) {}
    Transform(float x, float y, float z, float rx, float ry, float rz) : Position(x, y, z), Rotation(rx, ry, rz), Scale(1.0f, 1.0f, 1.0f) {}
};