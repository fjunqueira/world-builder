#include "glm/ext.hpp"
#include "player_input_handler.h"
#include <iostream>

void PlayerInputHandler::RotateObject(float cursor_x, float cursor_y, int width, int height, GameObject& sphere)
{
    glm::vec3 origin((float)width / 2, (float)height / 2, 0);

    glm::vec3 release_mouse_position(cursor_x, cursor_y, 0);

    glm::vec3 input(glm::normalize(release_mouse_position - origin));

    glm::vec3 world_x(1.0f, 0.0f, 0.0f);
    glm::vec3 world_z(0.0f, 0.0f, 1.0f);

    glm::mat4 rotation = glm::rotate(glm::radians(-input.x), world_z) * glm::rotate(glm::radians(input.y), world_x);

    sphere.apply_transformation(rotation);
}