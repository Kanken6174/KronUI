#include "./KronUIGL/KronUIGL.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == 0x824C ? "** GL ERROR **" : "" ),
            type, severity, message );
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(){
    std::cout << "begin" << std::endl;
    KronUIWindow* window = new KronUIWindow("test", 800, 600); 
    std::cout << "KronUIWindow" << std::endl;
    KronUIWindowManager::setWindow(window);
    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( MessageCallback, 0 ); std::cout << "callback" << std::endl;
    double time = glfwGetTime();
    float heading = 0;
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    EmptyRectangle* er = new EmptyRectangle(glm::vec3(0,0,0),0.5,0.5,0.1);
    
    GeometryRenderer* gr = new GeometryRenderer();
    er->generateVertices();
    gr->addShapeToBuffer(er);

    Shader* rps = new Shader("","./../shaders/text.vs", "./../shaders/text.fs");
    Shader shader = Shader("","./../shaders/text.vs", "./../shaders/text.fs");
    er->shader = rps;
    //rps->SetPlacementMatrix(1,1,0.5,0.5,0.5);
    TrueTypeManager* ttm = new TrueTypeManager("./f2.ttf");
    TextRenderer tx = TextRenderer(shader,window,ttm);
    float i = 0;
    while (!glfwWindowShouldClose(window->getSelf()))
    {
        if(glfwGetTime()-time > 0.01){
            time = glfwGetTime();
            heading++;
            if(heading >= 360)
                heading = 0;
        }
        processInput(window->getSelf());

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Draw the compass
        glBindVertexArray(VertexArrayID);
        er->drawSelf();
        tx.RenderText("test", (window->_width/2.5), window->_height/2, i, glm::vec3(1.0f,1.0f,1.0f));
        i+= 0.001f;
        glfwSwapBuffers(KronUIWindowManager::getWindow()->getSelf());
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}