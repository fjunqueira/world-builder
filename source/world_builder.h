#ifndef WORLD_BUILDER_WORLD_BUILDER_H
#define WORLD_BUILDER_WORLD_BUILDER_H

#include "buffer_utils.h"
#include "game_object.h"
#include "glm/gtx/transform.hpp"
#include "obj-loader/material.h"
#include <algorithm>
#include <iostream>
#include <unordered_map>

class WorldBuilder
{

  public:
    GameObject PlaceGameElementAtFace(int face_id, glm::vec3 face_normal, float world_radius,
                                      VertexArrayObject& object);

    bool IsFaceOccupied(int face_id);

    void material_mode(bool value);

    void selected_material(const std::string& material);

    const bool& material_mode() const;

    Material selected_material() const;

    const std::vector<int>& occupied_faces() const;

  private:
    std::vector<int> occupied_faces_;

    std::string selected_material_ = "grass";

    bool material_mode_ = false;

    std::unordered_map<std::string, Material> materials_ = {
        {"grass", Material(glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.2f, 0.5f, 0.0f), glm::vec3(0.5, 0.5, 0.5), FLT_MAX)},
        {"water", Material(glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.45f, 0.73f, 0.98), glm::vec3(0.5, 0.5, 0.5), 3.0f)},
        {"sand", Material(glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.93f, 0.86f, 0.43f), glm::vec3(0.5, 0.5, 0.5), 20.0f)}};
};
#endif // WORLD_BUILDER_WORLD_BUILDER_H