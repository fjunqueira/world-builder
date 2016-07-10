//
// Created by fabio on 4/10/16.
//

#include "mtl_reader.h"

std::map<std::string, Material>* MtlReader::ReadMaterials(const std::string& file_path) const
{
    std::map<std::string, Material>* materials = new std::map<std::string, Material>();
    std::string current_material;

    std::ifstream file(file_path, std::ios::in);
    
    if (file.is_open())
    {
        while (!file.eof())
        {
            std::string prefix;
            file >> prefix;

            if (prefix.compare("#") == 0)
                file.ignore();

            else if (prefix.compare("newmtl") == 0)
            {
                file >> current_material;
                materials->insert(std::pair<std::string, Material>(current_material, Material()));
            }
            else if (prefix.compare("Ka") == 0)
                materials->at(current_material).set_ambient(this->ReadVector3(file));

            else if (prefix.compare("Kd") == 0)
                materials->at(current_material).set_diffuse(this->ReadVector3(file));

            else if (prefix.compare("Ks") == 0)
                materials->at(current_material).set_specular(this->ReadVector3(file));

            else if (prefix.compare("Ns") == 0)
            {
                float shininess;
                file >> shininess;

                materials->at(current_material).set_shininess(shininess);
            }
            else if (prefix.compare("map_Kd") == 0)
            {
                std::string texture_file;
                file >> texture_file;

                materials->at(current_material).set_texture_file(texture_file);
            }
            else
                file.ignore();
        }
    }
    else
    {
        std::cout << "MtlReader: Unable to open file" << file_path;
        throw std::exception();
    }

    return materials;
}

glm::vec3 MtlReader::ReadVector3(std::ifstream& file) const
{
    float x, y, z;

    file >> x;
    file >> y;
    file >> z;

    return glm::vec3(x, y, z);
}
