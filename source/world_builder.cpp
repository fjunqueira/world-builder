#include "world_builder.h"

GameObject WorldBuilder::PlaceGameElementAtFace(int face_id, glm::vec3 face_normal, float world_radius,
                                                VertexArrayObject& vao)
{
    this->occupied_faces_.push_back(face_id);

    glm::vec3 world_up(0, 1, 0);

    glm::vec3 rotation_axis = glm::cross(glm::normalize(world_up), glm::normalize(face_normal));

    float angle = glm::asin(glm::length(rotation_axis));

    glm::mat4 rotation = glm::rotate(angle, rotation_axis);

    glm::mat4 transformation = glm::translate(glm::normalize(face_normal) * (float)world_radius) * rotation;

    return GameObject(vao, transformation);
}

bool WorldBuilder::IsFaceOccupied(int face_id)
{
    return std::find(this->occupied_faces_.begin(), this->occupied_faces_.end(), face_id) !=
           this->occupied_faces_.end();
}

void WorldBuilder::material_mode(bool value) { this->material_mode_ = value; }

void WorldBuilder::selected_material(const std::string& material) { this->selected_material_ = material; }

const bool& WorldBuilder::material_mode() const { return this->material_mode_; }

Material WorldBuilder::selected_material() const { return this->materials_.at(this->selected_material_); }

const std::vector<int>& WorldBuilder::occupied_faces() const { return this->occupied_faces_; }