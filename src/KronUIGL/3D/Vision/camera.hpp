#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


#include "../entity.hpp"

class Camera : public Entity {
public:
    glm::mat4 projectionMatrix = glm::mat4(0.0f);
    glm::mat4 viewMatrix = glm::mat4(0.0f);
    glm::quat rotationQuat = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));

    Camera(float width, float height, float nearPlane = 0.1f, float farPlane = 100.0f);

    void updateViewMatrix();

    void translate(glm::vec3 translation) {
        position += translation;
        updateViewMatrix();
    }

    void rotate(glm::vec3 rotation) {
        glm::quat qPitch = glm::angleAxis(glm::radians(rotation.x), getRight());
        glm::quat qYaw = glm::angleAxis(glm::radians(rotation.y), getUp());
        glm::quat qRoll = glm::angleAxis(glm::radians(rotation.z), getForward());
        glm::quat orientation = qPitch * qYaw * qRoll;
        rotationQuat = glm::normalize(orientation * rotationQuat);
        updateViewMatrix();
    }

    
    glm::vec3 getRotation() const {
        return rotation;
    }

    glm::vec3 getForward() const;
    glm::vec3 getUp() const;
    glm::vec3 getRight() const;

    Camera(){
        
    }
};