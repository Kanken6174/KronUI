#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "./entity.hpp"

class Camera : public Entity {
public:
    glm::mat4 projectionMatrix = glm::mat4(0.0f);
    glm::mat4 viewMatrix = glm::mat4(0.0f);

    Camera(float width, float height, float nearPlane = 0.1f, float farPlane = 100.0f);

    void updateViewMatrix();

    void translate(glm::vec3 translation) {
        position += translation;
        updateViewMatrix();
    }

    void rotate(glm::vec3 rotation) {
        this->rotation += rotation;
        updateViewMatrix();
    }
    Camera(){
        
    }
};