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
    //debugging only
    unsigned int quadVAO = 0;
    unsigned int quadVBO;
    void prepareQuad();
    void drawQuad();
public:
    std::shared_ptr<Shader> shader;
    MeshRenderer(std::shared_ptr<Shader> _shader) : shader(_shader) {}

    void addMesh(std::shared_ptr<Mesh> mesh) {
        mesh->Draw = [this, mesh]() { this->drawMesh(mesh); };
        mesh->setupMesh(shader->ID);
        meshes.push_back(mesh);
    }

    void drawMesh(std::shared_ptr<Mesh> mesh);

    void renderAll();
};