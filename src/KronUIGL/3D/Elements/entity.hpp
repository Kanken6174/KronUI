#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <optional>
#include "transform.hpp"
#include "texture.hpp"
#include "mesh.hpp"

/*
* this class is used to represent an entity in 3D space
*/
class Entity {
public:
    // stores the entity's XYZ rotation and translation + scale
    Transform transform;
    
    // this is used to store the children of this entity as part of the scene graph
    std::vector<Entity> children;
    std::optional<Entity*> parent = std::nullopt;

    // an entity can have a 3d mesh
    std::optional<Mesh> mesh = std::nullopt;

    Entity() {}
    Entity(float x, float y, float z) : transform(x,y,z) {}
    Entity(float x, float y, float z, float rx, float ry, float rz) : transform(x,y,z,rx,ry,rz) {}
};