//
// Created by fabio on 3/15/16.
//

#include "material.h"

Material::Material() {}

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
    : ambient_(ambient), diffuse_(diffuse), specular_(specular), shininess_(shininess)
{
}

void Material::set_ambient(const glm::vec3& vector) { this->ambient_ = vector; }

void Material::set_diffuse(const glm::vec3& vector) { this->diffuse_ = vector; }

void Material::set_specular(const glm::vec3& vector) { this->specular_ = vector; }

void Material::set_shininess(const float& shininess) { this->shininess_ = shininess; }

void Material::set_texture_file(const std::string& texture_file) { this->texture_file_ = texture_file; }

const glm::vec3& Material::ambient() const { return this->ambient_; }

const glm::vec3& Material::diffuse() const { return this->diffuse_; }

const glm::vec3& Material::specular() const { return this->specular_; }

const float& Material::shininess() const { return this->shininess_; }

const std::string& Material::texture_file() const { return this->texture_file_; }
