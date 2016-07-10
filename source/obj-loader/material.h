//
// Created by fabio on 3/15/16.
//

#ifndef WORLD_BUILDER_MATERIAL_H
#define WORLD_BUILDER_MATERIAL_H

#include "glm/glm.hpp"
#include <string>

class Material
{
  public:
    Material();

    Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);

    void set_ambient(const glm::vec3& vector);

    void set_diffuse(const glm::vec3& vector);

    void set_specular(const glm::vec3& vector);

    void set_shininess(const float& shininess);

    void set_texture_file(const std::string& texture_file);

    const glm::vec3& ambient() const;

    const glm::vec3& diffuse() const;

    const glm::vec3& specular() const;

    const float& shininess() const;

    const std::string& texture_file() const;

  private:
    glm::vec3 ambient_;
    glm::vec3 diffuse_;
    glm::vec3 specular_;
    float shininess_;
    std::string texture_file_;
};

#endif // WORLD_BUILDER_MATERIAL_H
