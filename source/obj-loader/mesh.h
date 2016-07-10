//
// Created by fabio on 3/15/16.
//

#ifndef WORLD_BUILDER_MESH_H
#define WORLD_BUILDER_MESH_H


#include <map>
#include "glm/glm.hpp"
#include <algorithm>
#include "face.h"
#include "group.h"
#include "material.h"

class Mesh
{
public:
    Mesh(const float& bounding_sphere_radius,
         const std::string& material_lib,
         const std::vector<glm::vec3>& vertices,
         const std::vector<glm::vec3>& normals,
         const std::vector<glm::vec3>& texture_mappings,
         const std::map<std::string, Group>& groups);

    const std::vector<glm::vec3>& vertices() const;

    const std::vector<glm::vec3>& normals() const;

    const std::vector<glm::vec3>& texture_mappings() const;

    const std::map<std::string, Group>& groups() const;

    const float& bounding_sphere_radius() const;

    const std::string& material_lib() const;

    virtual ~Mesh();

private:
    float bounding_sphere_radius_;
    std::string material_lib_;
    std::vector<glm::vec3> vertices_;
    std::vector<glm::vec3> normals_;
    std::vector<glm::vec3> texture_mappings_;
    std::map<std::string, Group> groups_;
    std::vector<std::string> disabled_groups_;
};


#endif //WORLD_BUILDER_MESH_H
