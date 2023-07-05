#include "./KronUIGL/KronUIGL.hpp"
#include "./KronUIGL/3D/camera.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

// Initialize camera
Camera camera = Camera(800, 600, 0.1f, 100.0f); // Adjust these parameters according to your needs

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
  fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", (type == GL_DEBUG_OUTPUT ? "** GL ERROR **" : ""), type, severity, message);
}

void processInput(GLFWwindow* window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.translate(glm::vec4(0.0f, 0.0f, -0.1f, 1.0f));
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.translate(glm::vec4(0.0f, 0.0f, 0.1f, 1.0f));
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.translate(glm::vec4(-0.1f, 0.0f, 0.0f, 1.0f));
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.translate(glm::vec4(0.1f, 0.0f, 0.0f, 1.0f));

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.rotate(glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f));
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.rotate(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera.rotate(glm::vec4(0.0f, -1.0f, 0.0f, 0.0f));
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera.rotate(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
}

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
    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    // Update camera rotation
    camera.rotate(glm::vec3(yoffset, xoffset, 0.0f));
}

int main(){
    std::cout << "begin" << std::endl;
    KronUIWindow* window = new KronUIWindow("test", 800, 600); 
    std::cout << "KronUIWindow" << std::endl;
    KronUIWindowManager::setWindow(window);
    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( MessageCallback, 0 ); std::cout << "callback" << std::endl;
    glfwSetCursorPosCallback(window->getSelf(), mouse_callback);

    double time = glfwGetTime();
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    EmptyRectangle* er = new EmptyRectangle(glm::vec3(0.5,0.5,0),0.7,0.5,0.1);
    DefaultCube* dc = new DefaultCube();
    
    GeometryRenderer* gr = new GeometryRenderer();
    gr->addShapeToBuffer(er);
    gr->addShapeToBuffer(dc);

    Shader* rps = new Shader("","./../shaders/geom.vs", "./../shaders/geom.fs");
    Shader* cubed = new Shader("","./../shaders/cube.vs", "./../shaders/cube.fs");
    Shader shader = Shader("","./../shaders/text.vs", "./../shaders/text.fs");
    er->shader = rps;
    dc->shader = cubed;
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    dc->shader->use();
    dc->shader->setMat4("model", modelMatrix); 
    //dc->shader->setMat4("view", camera.viewMatrix);
    //dc->shader->setMat4("projection", camera.projectionMatrix);
    //rps->SetPlacementMatrix(1,1,0.5,0.5,0.5);
    TrueTypeManager* ttm = new TrueTypeManager("./f2.ttf");
    TextRenderer tx = TextRenderer(shader,window,ttm);
    float i = 0;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    while (!glfwWindowShouldClose(window->getSelf()))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window->getSelf(), deltaTime);

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VertexArrayID);
        glDisable(GL_CULL_FACE);
        er->drawSelf();
        glEnable(GL_CULL_FACE);
        dc->shader->use();
        dc->shader->setMat4("view", camera.viewMatrix);
        dc->shader->setMat4("projection", camera.projectionMatrix);
        dc->drawSelf();
        tx.RenderText("test", (window->_width/2.5), window->_height/2, i, glm::vec3(1.0f,1.0f,1.0f));
        i+= 0.001f;
        glfwSwapBuffers(KronUIWindowManager::getWindow()->getSelf());
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}