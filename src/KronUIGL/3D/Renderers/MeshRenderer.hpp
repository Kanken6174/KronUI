#pragma once

#include <vector>
#include <memory>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../Shaders/Shader.hpp"
#include "../Loaders/OBJLoader.hpp"

class MeshRenderer {
private:
    std::vector<std::shared_ptr<Mesh>> meshes;

public:
    std::shared_ptr<Shader> shader;
    MeshRenderer(std::shared_ptr<Shader> shader) : shader(shader) {}

    void addMesh(std::shared_ptr<Mesh> mesh) {
        mesh->Draw = [this, mesh]() { this->drawMesh(mesh); };
        mesh->setupMesh();
        meshes.push_back(mesh);
    }

    void drawMesh(std::shared_ptr<Mesh> mesh);

    void renderAll();
};