#ifndef WORLD_BUILDER_RENDERER_H
#define WORLD_BUILDER_RENDERER_H

#include "game_object.h"
#include "glm/gtc/matrix_transform.hpp"
#include "shader_program.h"

class Renderer
{
  public:
    Renderer();

    void RenderGameObject(const GameObject& game_object, int width, int height) const;

    void RenderGameObjectForPicking(const GameObject& game_object, int width, int height) const;

    const ShaderProgram& game_object_program() const;

    const ShaderProgram& game_object_picking_program() const;

  private:
    void Render(GLuint program_id, const GameObject& game_object, int width, int height) const;

    ShaderProgram game_object_program_;
    ShaderProgram game_object_picking_program_;
};

#endif // WORLD_BUILDER_RENDERER_H