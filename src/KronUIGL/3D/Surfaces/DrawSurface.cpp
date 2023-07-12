#include "DrawSurface.hpp"
#include <GL/glew.h>
#include "../../../../include/logger.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

DrawSurface::DrawSurface(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::shared_ptr<Transform> transform)
    : vertices(std::move(vertices)), indices(std::move(indices)), transform(std::move(transform))
{
    glGenBuffers(1, &PBO);
}

DrawSurface::DrawSurface(const glm::vec2& size, std::vector<unsigned int> indices, std::shared_ptr<Transform> transform)
    : indices(std::move(indices)), transform(std::move(transform))
{
    Rectangle rect = Rectangle(size);
    std::vector<float> vertices = rect.generateVertices();
    for (int i = 0; i < vertices.size(); i += 3) {
        Vertex v;
        v.Position = glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]);
        // Texture coordinates. You'll need to adjust these if your vertices aren't arranged in a simple rectangle.
        v.TexCoords = glm::vec2(vertices[i], vertices[i + 1]);
        v.Normal = glm::vec3(0.0f, 0.0f, 0.0f);
        this->vertices.push_back(v);
    }
    glGenBuffers(1, &PBO);
}

void DrawSurface::setupSurface(GLuint textureId, GLuint PBO) {
    this->textureId = textureId;
    this->PBO = PBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // Vertex positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void DrawSurface::setupSurface() {
    // Generate and bind a new texture object
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Generate random pixel data
    int width = 1024;
    int height = 1024;
    std::vector<unsigned char> pixelData(3 * width * height);
    for (auto& pixel : pixelData) {
        pixel = std::rand() % 256; // Random value between 0 and 255
    }

    // Allocate and populate texture memory
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixelData.data());

    // Proceed as in the original method
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // Vertex positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void DrawSurface::updateSurface(const void* pixelData, GLsizeiptr size) {
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, PBO);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, size, pixelData, GL_STREAM_DRAW);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 1024, 1024, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

void DrawSurface::updateSurfaceRandom() {
    // Generate new random pixel data
    int width = 1024;
    int height = 1024;
    std::vector<unsigned char> pixelData(3 * width * height);
    for (int i = 0; i < pixelData.size(); i += 3) {
        pixelData[i + 0] = std::rand() % 256; // Random value for red
        pixelData[i + 1] = std::rand() % 256; // Random value for green
        pixelData[i + 2] = std::rand() % 256; // Random value for blue
    }

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Update the texture with the new pixel data
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixelData.data());
}

void DrawSurface::drawSurface(glm::mat4 &view, glm::mat4 &projection) {
    shader->use(); // Activate the shader program. `Shader` is a hypothetical class that encapsulates OpenGL shaders.
    // Set the shader uniforms for the model, view, and projection matrices.
    // `transform->getMatrix()` is a hypothetical function that returns the model matrix for this surface.
    glm::mat4 model = transform->getTransformMatrix();
    shader->setMat4("model", model); 
    // Bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Tell the shader that texture unit 0 (which we activated and bound the texture to) should be used for the "texture1" sampler
    shader->setInt("texture1", 0);

    // Draw the surface
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
