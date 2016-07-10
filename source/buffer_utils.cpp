#include "buffer_utils.h"

// Only meshes made only of triangles are allowed
VertexArrayObject buffer_utils::CreateVertexArrayObject(const std::vector<glm::vec3>& vertices,
                                                        const std::vector<glm::vec3>& normals)
{
    VertexBufferObject vertices_vbo = buffer_utils::CreateVertexBufferObject(vertices);
    VertexBufferObject normals_vbo = buffer_utils::CreateVertexBufferObject(normals);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    buffer_utils::BindBuffer(0, 3, vertices_vbo.id());

    buffer_utils::BindBuffer(1, 3, normals_vbo.id());

    return VertexArrayObject(vao, vertices_vbo, normals_vbo);
}

VertexArrayObject
buffer_utils::CreateVertexArrayObject(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals,
                                      const std::vector<glm::vec3>& ambient, const std::vector<glm::vec3>& specular,
                                      const std::vector<glm::vec3>& diffuse, const std::vector<float>& shininess)
{
    VertexBufferObject vertices_vbo = buffer_utils::CreateVertexBufferObject(vertices);
    VertexBufferObject normals_vbo = buffer_utils::CreateVertexBufferObject(normals);
    VertexBufferObject ambient_vbo = buffer_utils::CreateVertexBufferObject(ambient);
    VertexBufferObject specular_vbo = buffer_utils::CreateVertexBufferObject(specular);
    VertexBufferObject diffuse_vbo = buffer_utils::CreateVertexBufferObject(diffuse);
    VertexBufferObject shininess_vbo = buffer_utils::CreateVertexBufferObject(shininess);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    buffer_utils::BindBuffer(0, 3, vertices_vbo.id());

    buffer_utils::BindBuffer(1, 3, normals_vbo.id());

    buffer_utils::BindBuffer(2, 3, ambient_vbo.id());

    buffer_utils::BindBuffer(3, 3, specular_vbo.id());

    buffer_utils::BindBuffer(4, 3, diffuse_vbo.id());

    buffer_utils::BindBuffer(5, 1, shininess_vbo.id());

    return VertexArrayObject(vao, vertices_vbo, normals_vbo, ambient_vbo, specular_vbo, diffuse_vbo, shininess_vbo);
}

template <typename T>
void buffer_utils::UpdateVertexBufferObjectFace(int face_index, int vao_id, int vbo_id, T const* const data)
{
    glBindVertexArray(vao_id);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(T) * face_index, sizeof(T) * 3, data);
}

template <typename T> void buffer_utils::UpdateVertexBufferObject(int vao_id, int vbo_id, T const* const data, int size)
{
    glBindVertexArray(vao_id);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(T) * size, data);
}

VertexArrayObject buffer_utils::CreateFacePickingVertexArrayObject(const std::vector<glm::vec3>& vertices)
{
    VertexBufferObject vertices_vbo = buffer_utils::CreateVertexBufferObject(vertices);

    std::vector<glm::vec3> ids;
    for (int i = 1; i <= vertices.size() / 3; i++)
    {
        int r = (i & 0x000000FF) >> 0;
        int g = (i & 0x0000FF00) >> 8;
        int b = (i & 0x00FF0000) >> 16;

        ids.push_back(glm::vec3(r / 255.0f, g / 255.0f, b / 255.0f));
        ids.push_back(glm::vec3(r / 255.0f, g / 255.0f, b / 255.0f));
        ids.push_back(glm::vec3(r / 255.0f, g / 255.0f, b / 255.0f));
    }

    VertexBufferObject picking_vbo = buffer_utils::CreateVertexBufferObject(ids);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    buffer_utils::BindBuffer(0, 3, vertices_vbo.id());

    // Use the picking color in location 10 to avoid confusion
    buffer_utils::BindBuffer(10, 3, picking_vbo.id());

    return VertexArrayObject(vao, vertices_vbo, picking_vbo);
}

void buffer_utils::BindBuffer(GLuint location, GLint size, GLuint id)
{
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, 0, NULL);
}

template <typename T> VertexBufferObject buffer_utils::CreateVertexBufferObject(const std::vector<T>& data)
{
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), &data[0], GL_DYNAMIC_DRAW);

    return VertexBufferObject(vbo, data.size());
}

template VertexBufferObject buffer_utils::CreateVertexBufferObject<float>(const std::vector<float>& data);

template VertexBufferObject buffer_utils::CreateVertexBufferObject<glm::vec3>(const std::vector<glm::vec3>& data);

template void buffer_utils::UpdateVertexBufferObjectFace<float>(int face_index, int vao_id, int vbo_id,
                                                                float const* const data);

template void buffer_utils::UpdateVertexBufferObjectFace<glm::vec3>(int face_index, int vao_id, int vbo_id,
                                                                    glm::vec3 const* const data);

template void buffer_utils::UpdateVertexBufferObject<float>(int vao_id, int vbo_id, float const* const data, int size);

template void buffer_utils::UpdateVertexBufferObject<glm::vec3>(int vao_id, int vbo_id, glm::vec3 const* const data,
                                                                int size);