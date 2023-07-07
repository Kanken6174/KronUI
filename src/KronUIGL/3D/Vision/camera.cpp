#include "camera.hpp"

Camera::Camera(float width, float height, float nearPlane, float farPlane)
    : Entity(0.0f, 0.0f, 0.0f),
      projectionMatrix(glm::perspective(glm::radians(45.0f), width / height, nearPlane, farPlane)),
      viewMatrix(glm::lookAt(position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))) 
      {}

void Camera::updateViewMatrix() {
    viewMatrix = glm::lookAt(position, position + getForward(), getUp());
}

glm::vec3 Camera::getForward() const {
    return glm::normalize(glm::rotate(rotationQuat, glm::vec3(0.0f, 0.0f, -1.0f)));
}

glm::vec3 Camera::getUp() const {
    return glm::normalize(glm::cross(getRight(), getForward()));
}

glm::vec3 Camera::getRight() const {
   return glm::normalize(glm::cross(getForward(), glm::vec3(0.0f, 1.0f, 0.0f)));
}