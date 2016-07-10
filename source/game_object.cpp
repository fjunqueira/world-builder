#include "game_object.h"

GameObject::GameObject(const VertexArrayObject& vao, const VertexArrayObject& picking_vao, const glm::mat4& model_matrix)
    : vao_(vao), picking_vao_(picking_vao), model_matrix_(model_matrix)
{
}

GameObject::GameObject(){}

GameObject::GameObject(const VertexArrayObject& vao, const glm::mat4& model_matrix)
    : vao_(vao),  model_matrix_(model_matrix)
{
}

const glm::mat4& GameObject::model_matrix() const
{
    return this->model_matrix_;
}

const VertexArrayObject& GameObject::vao() const
{
    return this->vao_;
}

const VertexArrayObject& GameObject::picking_vao() const
{
    return this->picking_vao_;
}

void GameObject::apply_transformation(const glm::mat4& transformation)
{
    this->model_matrix_ = transformation * this->model_matrix_;
}