#include "camera.hpp"

Camera::Camera(float width, float height, float nearPlane, float farPlane)
    : Entity(0.0f, 0.0f, 0.0f),
      projectionMatrix(glm::perspective(glm::radians(45.0f), width / height, nearPlane, farPlane)),
      viewMatrix(glm::lookAt(position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))) 
      {}

void Camera::updateViewMatrix() {
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, position);
    transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    viewMatrix = glm::inverse(transform);
}