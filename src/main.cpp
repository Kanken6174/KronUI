#include "./KronUIGL/KronUIGL.hpp"
#include "./KronUIGL/Input/Input.hpp"
#include "./KronUIGL/Shaders/ShaderManager.hpp"

#include "./KronUIGL/3D/Renderers/MeshRenderer.hpp"

#include "../include/logger.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <chrono>
#include <thread>


void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    Logger::Level log_level;

    switch(severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:
            log_level = Logger::Level::ERROR;
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            log_level = Logger::Level::WARNING;
            break;
        case GL_DEBUG_SEVERITY_LOW:
            log_level = Logger::Level::INFO;
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
        default:
            log_level = Logger::Level::INFO;
            break;
    }

    std::string log_message = "GL CALLBACK: ";
    if (type == GL_DEBUG_OUTPUT) log_message += "** GL ERROR ** ";
    log_message += "type = 0x" + std::to_string(type) + ", severity = 0x" + std::to_string(severity) + ", message = " + std::string(message);

    Logger::getInstance().log(log_level, log_message);
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

    DefaultCube* dc = new DefaultCube(10.0f,0.5f,10.0f, 0.0f, -0.5f, 0.0f);
    
    OBJLoader* loader = new OBJLoader();

    std::vector<std::shared_ptr<Mesh>> ms = loader->loadModel("./Ressources/Models/laptop/t1.obj");
    std::cout << "meshes loaded: " << ms.size() << std::endl;

    std::unique_ptr<Entity> e = std::make_unique<Entity>();
    

    GeometryRenderer* gr = new GeometryRenderer();
    gr->addShapeToBuffer(dc);

    auto sme = std::make_shared<ShaderManager>();

    auto rps = std::make_shared<Shader>("./shaders/geom.vs", "./shaders/geom.fs");
    auto cubed = std::make_shared<Shader>("./shaders/cube.vs", "./shaders/cube.fs");
    auto shader = std::make_shared<Shader>("./shaders/text.vs", "./shaders/text.fs");

    MeshRenderer* mr = new MeshRenderer(cubed);
    for(auto mesh : ms){
        mr->addMesh(mesh);
    }
    sme->addShader(rps);
    sme->addShader(cubed);

    dc->shader = cubed;
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    dc->shader->use();
    dc->shader->setMat4("model", modelMatrix); 

    TrueTypeManager* ttm = new TrueTypeManager("./f2.ttf");
    TextRenderer tx = TextRenderer(shader.get(),window,ttm);
    float i = 0;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    const float frameTimeTarget = 1.0f / 60.0f; // Time for one frame at 60 FPS.
    while (!glfwWindowShouldClose(window->getSelf()))
    {
        float frameStart = glfwGetTime();
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window->getSelf(), deltaTime);

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VertexArrayID);

        dc->shader->use();
        dc->shader->setMat4("view", InputSystem::getInstance().getCamera().viewMatrix);
        dc->shader->setMat4("projection", InputSystem::getInstance().getCamera().projectionMatrix);
        dc->shader->setInt("useDefault", 1);
        dc->shader->setInt("useColor", 0);
        dc->shader->setInt("useTexture", 0);
        dc->shader->setInt("useBump", 0);
        dc->drawSelf();
        
        mr->shader->use();
        mr->shader->setMat4("view", InputSystem::getInstance().getCamera().viewMatrix);
        mr->shader->setMat4("projection", InputSystem::getInstance().getCamera().projectionMatrix);
        mr->renderAll();
        //tx.RenderText("test", (window->_width/2.5), window->_height/2, i, glm::vec3(1.0f,1.0f,1.0f));
        i+= 0.001f;
        glfwSwapBuffers(KronUIWindowManager::getWindow()->getSelf());
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}