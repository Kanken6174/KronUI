#include "ShaderManager.hpp"
#include <algorithm>

/// @brief set the currently used shader by opengl if it's not already used and is within the shader collection
/// @param s shader to be used
void ShaderManager::setShader(std::shared_ptr<Shader> s)
{
    if (std::any_of(shaders.begin(), shaders.end(), [&s](const auto& shader) { return shader->ID == s->ID; }))
    {
        if(!this->current.has_value() || this->current.value()->ID != s->ID){
            current = s;
        }
    }
}

/// @brief check if shader is present in the shader collection and if not add it
/// @param s shader to be added
void ShaderManager::addShader(std::shared_ptr<Shader> s)
{
    if (std::none_of(shaders.begin(), shaders.end(), [&s](const auto& shader) { return shader->ID == s->ID; }))
    {
        shaders.push_back(s);
    }
}

/// @brief check if shader is present in the shader collection and remove it
/// @param s shader to be removed
void ShaderManager::remShader(std::shared_ptr<Shader> s)
{
    auto it = std::find_if(shaders.begin(), shaders.end(), [&s](const auto& shader) { return shader->ID == s->ID; });
    if (it != shaders.end())
    {
        if (current.has_value() && current.value() == *it)
            current.reset();  // reset the current shader if it's the one being removed

        shaders.erase(it);
    }
}