#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

#include "../3D/camera.hpp"

class InputSystem{
    private:
        Camera camera = Camera(800, 600, 0.1f, 100.0f); 
        static InputSystem instance;
    public:
        Camera& getCamera() {return camera;}
        static inline InputSystem& getInstance() { return instance;}
};

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window, float deltaTime);