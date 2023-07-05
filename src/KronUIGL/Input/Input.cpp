#include "./Input.hpp"

InputSystem InputSystem::instance;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    static bool firstMouse = true;
    static float lastX = 400, lastY = 300;  // Initial position at the center

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX; 
    float yoffset = ypos - lastY;

    lastX = xpos;
    lastY = ypos;

    // Convert to float and scale down (these values depend on how you want to scale your camera's speed)
    float sensitivity = 0.15f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    // Update camera rotation
    InputSystem::getInstance().getCamera().rotate(glm::vec3(yoffset, xoffset, 0.0f));
}

void processInput(GLFWwindow* window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        InputSystem::getInstance().getCamera().translate(glm::vec4(0.0f, 0.0f, -0.1f, 1.0f));
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        InputSystem::getInstance().getCamera().translate(glm::vec4(0.0f, 0.0f, 0.1f, 1.0f));
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        InputSystem::getInstance().getCamera().translate(glm::vec4(-0.1f, 0.0f, 0.0f, 1.0f));
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        InputSystem::getInstance().getCamera().translate(glm::vec4(0.1f, 0.0f, 0.0f, 1.0f));

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        InputSystem::getInstance().getCamera().rotate(glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f));
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        InputSystem::getInstance().getCamera().rotate(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        InputSystem::getInstance().getCamera().rotate(glm::vec4(0.0f, -1.0f, 0.0f, 0.0f));
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        InputSystem::getInstance().getCamera().rotate(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
}
