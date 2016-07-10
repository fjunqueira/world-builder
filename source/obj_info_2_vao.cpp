#include "glm/ext.hpp"
#include "obj_info_2_vao.h"

VertexArrayObject ObjInfo2VAO::Adapt(Mesh* mesh, std::map<std::string, Material>* materials,
                                     std::map<std::string, GLuint>* textures)
{
    auto vertices = mesh->vertices();
    auto normals = mesh->normals();
    auto texture_mappings = mesh->texture_mappings();

    std::vector<glm::vec3> adapted_vertices;
    std::vector<glm::vec3> adapted_normals;
    std::vector<glm::vec3> adapted_ambient;
    std::vector<glm::vec3> adapted_specular;
    std::vector<glm::vec3> adapted_diffuse;
    std::vector<float> adapted_shininess;

    std::for_each(mesh->groups().begin(), mesh->groups().end(), [&](const std::pair<std::string, Group>& group) {

        auto group_info = group.second;

        std::for_each(group_info.faces().begin(), group_info.faces().end(), [&](const Face& face) {

            auto mappings_indexes = face.mappings_indexes();
            auto normals_indexes = face.normals_indexes();
            auto vertices_indexes = face.vertices_indexes();

            Material group_material;

            bool has_materials = materials != nullptr && materials->count(face.material());

            if (has_materials)
                group_material = materials->at(face.material());

            if (vertices_indexes.size() > 4)
                std::cout << "Faces with more than 4 vertices are not supported" << std::endl;
            else if (vertices_indexes.size() == 4)
                QuadToTriangle(vertices_indexes);

            if (normals_indexes.size() == 4)
                QuadToTriangle(normals_indexes);

            for (int i = 0; i < vertices_indexes.size(); ++i)
            {
                if (has_materials)
                {
                    adapted_ambient.push_back(group_material.ambient());

                    adapted_specular.push_back(group_material.specular());

                    adapted_diffuse.push_back(group_material.diffuse());
                    
                    adapted_shininess.push_back(group_material.shininess());
                }

                if (normals_indexes.size() > 0)
                    adapted_normals.push_back(normals.at(normals_indexes.at(i)));

                adapted_vertices.push_back(vertices.at(vertices_indexes.at(i)));
            }
        });
    });

    return buffer_utils::CreateVertexArrayObject(adapted_vertices, adapted_normals, adapted_ambient, adapted_specular,
                                                 adapted_diffuse, adapted_shininess);
}

void ObjInfo2VAO::QuadToTriangle(std::vector<int>& data)
{
    int last_vertex = data.back();
    data.pop_back();

    data.push_back(data.at(2));
    data.push_back(last_vertex);
    data.push_back(data.at(0));
}