#include "MeshRenderer.hpp"

void MeshRenderer::renderAll() {
    shader->use();

    glm::mat4 model = glm::mat4(1.0f);

    for (const std::shared_ptr<Mesh>& mesh : meshes) {
        // set the model matrix for the current mesh.
        model = mesh->getTransformMatrix();
        shader->setMat4("model", model);

        /*
        // Check the mesh's textures to enable or disable shader features.
        int useColor = 1, useTexture = 0, useBump = 0;

        if (!mesh->textures.empty()) {
            useTexture = 1;
            for (const auto& texture : mesh->textures) {
                if (texture.type == "texture_bump") {
                    useBump = 1;
                    break;
                }
            }
        }

        shader->setInt("useColor", useColor);
        shader->setInt("useTexture", useTexture);
        shader->setInt("useBump", useBump);
        */
        // Draw the mesh.
        mesh->Draw();
    }
}

void MeshRenderer::drawMesh(std::shared_ptr<Mesh> mesh) {
    glBindVertexArray(mesh->VAO);
    glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}