#ifndef guard_georenderer
#define guard_georenderer
#include <GL/glew.h>
#include "./Shapes.hpp"
#include <GLFW/glfw3.h>

#include <vector>
#include <map>

class GeometryRenderer{
private:
    std::vector<Drawable*> elements;
    std::map<int,float*> arrays;
public:
    void addShapeToBuffer(Drawable* toRender);
    void renderAll();
};

#endif