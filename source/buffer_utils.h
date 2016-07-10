#ifndef WORLD_BUILDER_BUFFER_UTILS_H
#define WORLD_BUILDER_BUFFER_UTILS_H

#include "glm/glm.hpp"
#include <GL/glew.h>
#include <vector>

class VertexBufferObject
{
  public:
    VertexBufferObject() {}
    VertexBufferObject(GLuint id, int size) : id_(id), size_(size) {}

    const GLuint& id() const { return this->id_; }

    const int& size() const { return this->size_; }

  private:
    GLuint id_;
    int size_;
};

class VertexArrayObject
{
  public:
    VertexArrayObject() {}

    VertexArrayObject(GLuint id, const VertexBufferObject& vertices, const VertexBufferObject& normals)
        : id_(id), vertices_(vertices), normals_(normals)
    {
    }

    VertexArrayObject(GLuint id, const VertexBufferObject& vertices, const VertexBufferObject& normals,
                      const VertexBufferObject& ambient, const VertexBufferObject& specular,
                      const VertexBufferObject& diffuse, const VertexBufferObject& shininess)
        : id_(id), vertices_(vertices), normals_(normals), ambient_(ambient), specular_(specular), diffuse_(diffuse),
          shininess_(shininess)
    {
    }

    const GLuint& id() const { return this->id_; }

    const VertexBufferObject& vertices() const { return this->vertices_; }

    const VertexBufferObject& normals() const { return this->normals_; }

    const VertexBufferObject& ambient() const { return this->ambient_; }

    const VertexBufferObject& specular() const { return this->specular_; }

    const VertexBufferObject& diffuse() const { return this->diffuse_; }

    const VertexBufferObject& shininess() const { return this->shininess_; }

  private:
    GLuint id_;
    VertexBufferObject vertices_;
    VertexBufferObject normals_;

    VertexBufferObject ambient_;
    VertexBufferObject specular_;
    VertexBufferObject diffuse_;
    VertexBufferObject shininess_;
};

namespace buffer_utils
{

VertexArrayObject CreateVertexArrayObject(const std::vector<glm::vec3>& vertices,
                                          const std::vector<glm::vec3>& normals);

VertexArrayObject CreateVertexArrayObject(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals,
                                          const std::vector<glm::vec3>& ambient, const std::vector<glm::vec3>& specular,
                                          const std::vector<glm::vec3>& diffuse, const std::vector<float>& shininess);

void BindBuffer(GLuint location, GLint size, GLuint id);

VertexArrayObject CreateFacePickingVertexArrayObject(const std::vector<glm::vec3>& vertices);

template <typename T> VertexBufferObject CreateVertexBufferObject(const std::vector<T>& data);

template <typename T> void UpdateVertexBufferObjectFace(int face_index, int vao_id, int vbo_id, T const* const data);

template <typename T> void UpdateVertexBufferObject(int vao_id, int vbo_id, T const* const data, int size);
};

#endif // WORLD_BUILDER_BUFFER_UTILS_H
