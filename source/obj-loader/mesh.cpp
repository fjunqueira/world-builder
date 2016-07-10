//
// Created by fabio on 3/15/16.
//

#include "mesh.h"

Mesh::Mesh(const float& bounding_sphere_radius,
           const std::string& material_lib,
           const std::vector<glm::vec3>& vertices,
           const std::vector<glm::vec3>& normals,
           const std::vector<glm::vec3>& texture_mappings,
           const std::map<std::string, Group>& groups)
        : bounding_sphere_radius_(bounding_sphere_radius),
          material_lib_(material_lib),
          vertices_(vertices),
          normals_(normals),
          texture_mappings_(texture_mappings),
          groups_(groups)
{

}

const float& Mesh::bounding_sphere_radius() const
{
    return this->bounding_sphere_radius_;
}

const std::string& Mesh::material_lib() const
{
    return this->material_lib_;
}

const std::map<std::string, Group>& Mesh::groups() const
{
    return this->groups_;
}

const std::vector<glm::vec3>& Mesh::texture_mappings() const
{
    return this->texture_mappings_;
}

const std::vector<glm::vec3>& Mesh::normals() const
{
    return this->normals_;
}

const std::vector<glm::vec3>& Mesh::vertices() const
{
    return this->vertices_;
}

Mesh::~Mesh()
{
}