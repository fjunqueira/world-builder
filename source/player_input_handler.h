#ifndef WORLD_BUILDER_PLAYER_INPUT_HANDLER_H
#define WORLD_BUILDER_PLAYER_INPUT_HANDLER_H

#include "game_object.h"
#include "GLFW/glfw3.h"
#include "glm/gtx/transform.hpp"

class PlayerInputHandler
{
  public:
    void RotateObject(float cursor_x, float cursor_y, int width, int height, GameObject& object);

  private:
    glm::vec3 initial_mouse_position_;
};

#endif // WORLD_BUILDER_PLAYER_INPUT_HANDLER_H