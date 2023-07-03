#include "./Shapes.hpp"
#include <algorithm>
#include <iterator>

Point::Point(glm::vec3 position) : shapeElement(), _position(position){
    vertices.clear();
    vertices.resize(VERTICES_SIZE);
    verticesAmount = VERTICES_SIZE;
}

Point::Point() : shapeElement(){
    vertices.clear();
    vertices.resize(VERTICES_SIZE);
    verticesAmount = VERTICES_SIZE;
}

Point::Point(const Point& p) : shapeElement(), _position(p._position){
    vertices.clear();
    vertices.resize(VERTICES_SIZE);
    verticesAmount = VERTICES_SIZE;
}

std::vector<float> Point::generateVertices(){
    vertices[0] = _position.x;
    vertices[1] = _position.y;
    vertices[2] = _position.z;
    std::cout << vertices.size() << std::endl;
    return vertices;
}

Line::Line(Point begin, Point end, float thickness) : shapeElement(), _begin(begin), _end(end), _thickness(thickness){
    vertices.clear();
    vertices.resize(2*VERTICES_SIZE);
    verticesAmount = 2*VERTICES_SIZE;
}

std::vector<float> Line::generateVertices(){
    std::vector<float> begin_vert = _begin.generateVertices();
    std::vector<float> end_vert = _end.generateVertices();
    for(int i = 0; i < VERTICES_SIZE; i++){
        vertices[i] = begin_vert[i];
        vertices[VERTICES_SIZE+i] = end_vert[i];
    }
    
    return vertices;
}

Triangle::Triangle(Point points[3]) : shapeElement(){
    vertices.clear();
    vertices.resize(3*VERTICES_SIZE);
    verticesAmount = 3*VERTICES_SIZE; std::cout << "amnt vert" <<std::endl;
    for(int i  = 0; i < 3; i++){ std::cout << "for point" <<std::endl;
        _points[i] = Point(points[i].getVector());
    }
}  

Triangle::Triangle() : shapeElement(){
    std::cout << "Tri constr" <<std::endl;
    vertices.clear();
    verticesAmount = 3*VERTICES_SIZE;
    vertices.resize(verticesAmount);
}

Triangle::Triangle(const Triangle& t) : shapeElement(){
    std::cout << "Tri copy" <<std::endl;
    vertices.clear();
    verticesAmount = 3*VERTICES_SIZE;
    vertices.resize(verticesAmount);
    for(int i  = 0; i < 3; i++){
        _points[i] = t._points[i];
    }
}

std::vector<float> Triangle::generateVertices(){
    for(int i  = 0; i < 3; i++){
        std::vector<float> verts = _points[i].generateVertices();
        for(int j = 0; j < VERTICES_SIZE; j++)
            vertices[i*VERTICES_SIZE+j] = verts[j];
    }
    return vertices;
}

Rectangle::Rectangle(Point points[4]) : shapeElement(){
    vertices.clear();
    verticesAmount = 2*3*VERTICES_SIZE;
    vertices.resize(verticesAmount);
    for(int i  = 0; i < 4; i++)
        _points[i] = points[i];
}

Rectangle::Rectangle() : shapeElement(){
    vertices.clear();
    verticesAmount = 2*3*VERTICES_SIZE;
    vertices.resize(verticesAmount);
}

Rectangle::Rectangle(const Rectangle& t) : shapeElement(){
    vertices.clear();
    verticesAmount = 2*3*VERTICES_SIZE;
    vertices.resize(verticesAmount);
    for(int i  = 0; i < 4; i++)
        _points[i] = t._points[i];
}

std::vector<float> Rectangle::generateVertices(){
    // First triangle
    Point ptArr1[3] = {Point(_points[0].getVector()), Point(_points[1].getVector()), Point(_points[2].getVector())};
    Triangle t1 = Triangle(ptArr1);
    std::vector<float> triangleVerts1 = t1.generateVertices();
    for(int j = 0; j < (3*VERTICES_SIZE); j++){
        vertices[j] = triangleVerts1[j];
    }

    // Second triangle
    Point ptArr2[3] = {Point(_points[1].getVector()), Point(_points[2].getVector()), Point(_points[3].getVector())};
    Triangle t2 = Triangle(ptArr2);
    std::vector<float> triangleVerts2 = t2.generateVertices();
    for(int j = 0; j < (3*VERTICES_SIZE); j++){
        vertices[3*VERTICES_SIZE+j] = triangleVerts2[j];
    }

    return vertices;
}

EmptyRectangle::EmptyRectangle(Point points[4], float thickness) : Drawable(),_thickness(thickness){
    mode = RenderMode::Triangles;
    vertices.clear();
    verticesAmount = 4*2*3*VERTICES_SIZE;   //4 rectangles, * 2 triangles * 3 points * Verticies size
    vertices.resize(verticesAmount);
    for(int i  = 0; i < 4; i++)
        _points[i] = points[i]; //setup the 4 corner points
    //get the width/height of the rectangle
    float width = std::abs(_points[0].getVector().x -_points[1].getVector().x);
    float height = std::abs(_points[1].getVector().y -_points[2].getVector().y);
}

EmptyRectangle::EmptyRectangle(glm::vec3 origin,float width, float height, float thickness) : Drawable(), _width(width), _height(height), _thickness(thickness){
    mode = RenderMode::Triangles;

    vertices.clear();
    //verticesAmount = 4*2*3*VERTICES_SIZE;   //4 rectangles, * 2 triangles * 3 points * Verticies size
    //vertices.resize(verticesAmount);

    glm::vec3 heightOffset = glm::vec3(0,height,0);
    glm::vec3 widthOffset = glm::vec3(width,0,0);

    _points[0] = Point(origin); //bottom left
    _points[1] = Point(origin + widthOffset); //bottom right
    _points[2] = Point(origin + heightOffset); //top left
    _points[3] = Point(origin + widthOffset + heightOffset); //top right
}

std::vector<float> EmptyRectangle::generateVertices(){
    std::cout << "in verts" <<std::endl;
    glm::vec3 YOffset = glm::vec3(0,_height,0);
    glm::vec3 XOffset = glm::vec3(_width,0,0);
    glm::vec3 thicknessOffSetX = glm::vec3(_thickness,0,0);
    glm::vec3 thicknessOffSetY = glm::vec3(0,_thickness,0);
    glm::vec3 centerPoint = glm::vec3(_width/2,_height/2,0);
    std::cout << "done offsets" <<std::endl;
    glm::vec3 origin = _points[0].getVector();
    
    //Y 
    //<thickness>
    //2***3***...
    //**  * next
    //* * ****...
    //*  **
    //0***1 X
    //*********
    //* previous
    //*********
    Point pointsA[4] = {Point(glm::vec3(origin)),                                  //bottom left
                        Point(glm::vec3(origin+thicknessOffSetX)),                 //bottom right
                        Point(glm::vec3(origin+YOffset)),                          //top left
                        Point(glm::vec3(origin+YOffset+thicknessOffSetX))  //top right
                        };
    _sides[0] = Rectangle(pointsA);

    //Y                    
    //2********************3    ↑
    //*         *          *    Thickness
    //0********************1 X  ↓
    //                *    *
    //                *next*
    origin = pointsA[3].getVector()-thicknessOffSetY;
    Point pointsB[4] = {Point(glm::vec3(origin)),    //bottom left
                        Point(glm::vec3(origin+XOffset)),    //bottom right
                        Point(glm::vec3(origin+thicknessOffSetY)),                //top left
                        Point(glm::vec3(origin+XOffset+thicknessOffSetY))     //top right
                        };
    _sides[1] = Rectangle(pointsB);
    //********
    //       *
    //***2***3
    //   **  *
    //**** * *
    //   *  **
    //***0***1
    origin = pointsB[1].getVector()-thicknessOffSetX-YOffset;
    Point pointsC[4] = {Point(glm::vec3(origin)),                                  //bottom left
                        Point(glm::vec3(origin+thicknessOffSetX)),                 //bottom right
                        Point(glm::vec3(origin+YOffset)),                          //top left
                        Point(glm::vec3(origin+YOffset+thicknessOffSetX+XOffset))  //top right
                        };
    _sides[2] = Rectangle(pointsC);

    //Y
    //* N *            * P *
    //2****************3   *    ↑
    //*         *      *   *    Thickness
    //0****************1**** X  ↓
    //
    //
    origin = pointsC[0].getVector()-thicknessOffSetX;
    Point pointsD[4] = {Point(glm::vec3(origin)),    //bottom left
                        Point(glm::vec3(origin+XOffset)),    //bottom right
                        Point(glm::vec3(origin+thicknessOffSetY)),                //top left
                        Point(glm::vec3(origin+XOffset+thicknessOffSetY))     //top right
                        };
    _sides[3] = Rectangle(pointsD);
    //-------------------------------------
    std::cout << "done verts" <<std::endl;
    std::vector<float> sideVertices;
    for(int i = 0; i < 4; i++){
        sideVertices = _sides[i].generateVertices();
        std::cout << "sideVertices.size() " << sideVertices.size() << std::endl;

        // Print out the contents of sideVertices
        for(int j = 0; j < sideVertices.size(); j++) {
            std::cout << sideVertices[j] << " ";
        }
        std::cout << std::endl;

        std::cout << "vertices.size() before insertion " << vertices.size() << std::endl;
        vertices.insert(vertices.end(), sideVertices.begin(), sideVertices.end());
        std::cout << "vertices.size() after insertion " << vertices.size() << std::endl;
    }

    
    return vertices;
}