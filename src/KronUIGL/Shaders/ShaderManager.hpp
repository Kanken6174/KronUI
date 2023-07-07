#include <vector>
#include <memory>
#include <optional>

#include "Shader.hpp"

class Shader;

/// @brief Manages shaders
class ShaderManager {
protected:
    std::vector<std::shared_ptr<Shader>> shaders;
    std::optional<std::shared_ptr<Shader>> current;
public:
    void setShader(std::shared_ptr<Shader> s);
    void addShader(std::shared_ptr<Shader> s);
    void remShader(std::shared_ptr<Shader> s);
};