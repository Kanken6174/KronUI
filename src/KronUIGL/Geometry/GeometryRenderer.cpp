#include "./GeometryRenderer.hpp"

//global invisible draw function stored in the object to draw (self call)
void drawGeometry(Drawable* toDraw){
    toDraw->shader->use();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(400), 0.0f, static_cast<float>(600));
    toDraw->shader->setMat4("projection", projection);
    toDraw->shader->setVec3("textColor", RED);
    switch(toDraw->mode){
        case RenderMode::Triangles:
                // 1st attribute buffer : vertices
                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, toDraw->bufferID);
                glVertexAttribPointer(
                0,                   // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                   //3 (xyz) per verticies
                GL_FLOAT,            // type
                GL_FALSE,            // normalized?
                0,                   // stride
                (void*)0             // array buffer offset
                );  
                glDrawArrays(GL_LINE_LOOP, 0, toDraw->verticesAmount/3); // Starting from vertex 0; 3 vertices total -> 1 triangle
                glDisableVertexAttribArray(0);
        break;
        default:
        break;
    }
}

void GeometryRenderer::addShapeToBuffer(Drawable* toRender){
    float* arr = new float[toRender->verticesAmount];
    std::vector<float> verticies = toRender->generateVertices();
    std::copy(verticies.begin(), verticies.end(), arr); //transfer data to the heap
    int i = 0;
    std::cout << std::endl;

    GLuint vertexhandle;
    glGenBuffers(1, &vertexhandle);
    glBindBuffer(GL_ARRAY_BUFFER, vertexhandle);
    glBufferData(GL_ARRAY_BUFFER, toRender->verticesAmount, arr, GL_STATIC_DRAW);

    arrays[vertexhandle] = arr;

    toRender->bufferID = vertexhandle;
    toRender->drawerFunction = &drawGeometry;
    toRender->mode = RenderMode::Triangles;
}