#ifndef guard_drawing
#define guard_drawing
#include <GL/glew.h>
#include "../Shaders/RotationPaintShader.hpp"
#define VERTICES_SIZE 3
#include <vector>

enum class RenderMode {Triangles, Lines, Quads};

class shapeElement{
protected:
    std::vector<float> vertices = std::vector<float>();
public:
    /// @brief Generates the vertices for a given shape, which can be read by opengl to draw things
    /// @return 
    unsigned int verticesAmount = 3;
    virtual std::vector<float> generateVertices()=0;
};

class Drawable : public shapeElement{
public:
    RenderMode mode = RenderMode::Triangles;
    GLuint bufferID;
    Shader* shader;
    void (*drawerFunction)(Drawable*);
    void drawSelf(){
        if(drawerFunction != nullptr)
            drawerFunction(this);
        else
            std::cout << "drawer function was null on drawable: " << this->bufferID << std::endl;
    }
};

#endif