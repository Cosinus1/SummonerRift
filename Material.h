// For MTL reading purpose
#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include "glm/glm.hpp"

struct Material {
    std::string materialName; 
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    float transparency;
    float density;
    std::string diffuseMap;
    std::string specularMap;
};

#endif 
