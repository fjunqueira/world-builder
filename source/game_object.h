#ifndef WORLD_BUILDER_GAME_OBJECT_H
#define WORLD_BUILDER_GAME_OBJECT_H

#include "buffer_utils.h"

class GameObject
{
  public:
    GameObject();

    GameObject(const VertexArrayObject& vao, const VertexArrayObject& picking_vao, const glm::mat4& model_matrix);

    GameObject(const VertexArrayObject& vao, const glm::mat4& model_matrix);

    const glm::mat4& model_matrix() const;

    void apply_transformation(const glm::mat4& transformation);

    const VertexArrayObject& vao() const;

    const VertexArrayObject& picking_vao() const;

  private:
    VertexArrayObject vao_;
    VertexArrayObject picking_vao_;
    glm::mat4 model_matrix_;
};

#endif // WORLD_BUILDER_GAME_OBJECT_H
