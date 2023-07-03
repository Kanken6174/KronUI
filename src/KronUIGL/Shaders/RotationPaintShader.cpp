#include "./RotationPaintShader.hpp"

const std::string fragmentCode =    R"(#version 300 es
                                        precision mediump float;
                                        uniform vec3 paint;
                                        out vec3 color;
                                        void main(){
                                           color = paint;
                                        })";
const std::string vertexCode =      R"(#version 300 es
                                        precision mediump float;
                                        uniform mat4 transformation;
                                        in vec3 position;
                                        void main()
                                        {
                                            gl_Position = transformation * vec4(position, 1.0);
                                        })";

RotationPaintShader::RotationPaintShader(std::string reflectiveName):Shader(reflectiveName+"RotationPaintShader.",vertexCode,fragmentCode){
        std::cout << "use" << std::endl;
        use();std::cout << "SetPlacementMatrix" << std::endl;
        SetPlacementMatrix(1,0,0,0,0);std::cout << "setPaint" << std::endl;
        setPaint(0.5,0.5,0.5);
}

void RotationPaintShader::SetPlacementMatrix(float scale, float angle, float x, float y, float z){
    PlacementMatrix = glm::rotate(glm::mat4(scale), glm::radians(angle), glm::vec3(x,y,z));
    setMat4(transformation_var,PlacementMatrix);
}

void RotationPaintShader::setPaint(float R, float G, float B){
    Color = glm::vec3(R,G,B);
    setVec3(paint_var,Color);
}