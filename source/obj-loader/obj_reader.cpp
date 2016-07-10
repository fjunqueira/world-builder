//
// Created by fabio on 3/15/16.
//

#include "obj_reader.h"

Mesh* ObjReader::ReadMesh(const std::string& file_path) const
{
    std::ifstream file(file_path, std::ios::in);

    std::string material_lib;

    float bounding_sphere_radius = 0;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> texture_mappings;

    std::string current_material;

    std::string current_group("default");
    std::map<std::string, Group> groups;
    groups.insert(std::pair<std::string, Group>("default", Group("default")));

    if (file.is_open())
    {
        while (!file.eof())
        {
            std::string prefix;
            file >> prefix;

            if (prefix.compare("#") == 0)
                file.ignore();

            else if (prefix.compare("v") == 0)
            {
                auto vertex = this->ReadVector3(file);
                auto vertex_magnitude = vertex.length();

                if (vertex_magnitude > bounding_sphere_radius)
                    bounding_sphere_radius = vertex_magnitude;

                vertices.push_back(vertex);
            }
            else if (prefix.compare("vt") == 0)
                texture_mappings.push_back(this->ReadVector2(file));

            else if (prefix.compare("vn") == 0)
                normals.push_back(this->ReadVector3(file));

            else if (prefix.compare("f") == 0)
                groups.at(current_group).add_face(this->ReadFace(file, current_material));

            else if (prefix.compare("g") == 0 && file.peek() == ' ')
            {
                file >> current_group;

                if (groups.count(current_group) == 0)
                    groups.insert(std::pair<std::string, Group>(current_group, Group( current_group)));
            }
            else if (prefix.compare("usemtl") == 0)
                file >> current_material;

            else if (prefix.compare("mtllib") == 0)
                file >> material_lib;

            else
                file.ignore();
        }
    }
    else
    {
        std::cout << "ObjReader: Unable to open file" << file_path;
        throw std::exception();
    }

    return new Mesh(bounding_sphere_radius, material_lib, vertices, normals, texture_mappings, groups);
}

glm::vec3 ObjReader::ReadVector3(std::ifstream& file) const
{
    float x, y, z;

    file >> x;
    file >> y;
    file >> z;

    return glm::vec3(x, y, z);
}

glm::vec3 ObjReader::ReadVector2(std::ifstream& file) const
{
    float x, y;

    file >> x;
    file >> y;

    return glm::vec3(x, y, 0);
}

Face ObjReader::ReadFace(std::ifstream& file, const std::string& material) const
{
    std::vector<int> face_vertices;
    std::vector<int> face_normals;
    std::vector<int> face_mappings;

    std::string line;
    std::getline(file, line);

    line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());

    std::stringstream line_stream(line);

    std::regex regex(" *(\\d*)/?(\\d*)?/?(\\d*)? *");

    while (!line_stream.eof())
    {
        std::string data;
        std::smatch match;

        line_stream >> data;

        std::regex_match(data, match, regex);

        auto vertex = match.str(1);

        if (!vertex.empty())
            face_vertices.push_back(atoi(vertex.c_str()) - 1);

        auto mapping = match.str(2);

        if (!mapping.empty())
            face_mappings.push_back(atoi(mapping.c_str()) - 1);

        auto normal = match.str(3);

        if (!normal.empty())
            face_normals.push_back(atoi(normal.c_str()) - 1);
    }

    return Face(material, face_vertices, face_normals, face_mappings);
}
