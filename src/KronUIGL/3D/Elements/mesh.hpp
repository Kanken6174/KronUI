#pragma once

#include "vertex.hpp"
#include "texture.hpp"
#include "transform.hpp"

#include <GL/glew.h>
#include <functional>

class Mesh {
public:
    // Mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    Transform transform;

    unsigned int VAO, VBO, EBO,TBO;

    GLuint shaderID;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Transform transform);
    std::function<void()> Draw;
    glm::mat4 getTransformMatrix() const;

    void setupMesh(GLuint shaderProgram);
};