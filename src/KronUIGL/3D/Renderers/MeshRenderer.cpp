#include "MeshRenderer.hpp"

void MeshRenderer::prepareQuad()
{
    float quadVertices[] = {
        // positions        // texture coords
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,    
    };
    
    if (quadVAO == 0)
    {
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);

        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
}

void MeshRenderer::drawQuad()
{
    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);
}

void MeshRenderer::renderAll() {
    shader->use();

    glm::mat4 model = glm::mat4(1.0f);

    for (const std::shared_ptr<Mesh>& mesh : meshes) {
        // set the model matrix for the current mesh.
        model = mesh->getTransformMatrix();
        shader->setMat4("model", model);

        // Check the mesh's textures to enable or disable shader features.
        int useColor = 0, useTexture = 0, useBump = 0;
        unsigned int diffuseNr = 1;
        unsigned int normalNr = 1;

        //std::cout << "rendering model with: " << mesh->textures.size() << " textures" << std::endl;

        for (unsigned int i = 0; i < mesh->textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding

            // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = mesh->textures[i].type;
            if (name == "texture_diffuse") {
                number = std::to_string(diffuseNr++);
                useTexture = 1;
            } else if (name == "texture_bump") {
                number = std::to_string(normalNr++);
                useBump = 1;
            }
            shader->setInt(("material." + name + number).c_str(), i);
            glBindTexture(GL_TEXTURE_2D, mesh->textures[i].id);
        }
        shader->setInt("useDefault", (useColor == 0 && useTexture == 0 && useBump == 0) ? 1 : 0);
        shader->setInt("useColor", useColor);
        shader->setInt("useTexture", useTexture);
        shader->setInt("useBump", useBump);
        // Draw the mesh.
        mesh->Draw();

        // Always good practice to set everything back to defaults once configured.
        glActiveTexture(GL_TEXTURE0);
    }
}

void MeshRenderer::drawMesh(std::shared_ptr<Mesh> mesh) {
    glBindVertexArray(mesh->VAO);
    glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glEnable(GL_CULL_FACE);
}