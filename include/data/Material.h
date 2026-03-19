//
// Created by desktop on 26. 3. 19..
//

#ifndef TOYRENDERER2_MATERIAL_H
#define TOYRENDERER2_MATERIAL_H
#include <map>
#include <string>

#include "../library/Geometry.h"

struct Material {
    std::string name;
    Vec3 ambient;
    Vec3 diffuse;
    Vec3 specular;
    float shininess;
    std::string diffuse_map_path;
    Material() : shininess(0) {};
};

class MaterialManager {
public:
    std::map<std::string,Material> material;

    bool load_mtl(const std::string &path);
    const Material& get(const std::string& name) { return material[name]; }
};


#endif //TOYRENDERER2_MATERIAL_H