#ifndef Guard_RotationPaintShader
#define Guard_RotationPaintShader

#include "./Shader.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "./../Paints/Paints.hpp"

class RotationPaintShader : public Shader{
private:
    const std::string_view transformation_var = "transformation";
    const std::string_view paint_var = "paint";
    glm::mat4 PlacementMatrix;
    glm::vec3 Color = glm::vec3(GRAY);
public:
    RotationPaintShader(std::string_view reflectiveName = "");
    void SetPlacementMatrix(float scale, float angle, float x, float y, float z);
    void setPaint(float R, float G, float B);
    void UseShader() {use();}
};

#endif