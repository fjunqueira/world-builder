//
// Created by fabio on 4/23/16.
//

#include "obj_loader.h"

ObjInfo ObjLoader::LoadObj(const std::string& obj_path, const std::string& obj_name) const
{
    ObjReader obj_reader;
    MtlReader mtl_reader;

    ObjInfo obj_info;

    obj_info.mesh = obj_reader.ReadMesh(obj_path + obj_name);

    if (!obj_info.mesh->material_lib().empty())
    {
        obj_info.materials = mtl_reader.ReadMaterials(obj_path + obj_info.mesh->material_lib());
    }

    return obj_info;
}

std::vector<std::string> ObjLoader::GetTexturesToLoad(const std::string& obj_path, std::map<std::string, Material>* materials) const
{
    std::vector<std::string> textures_to_load;

    std::for_each(materials->begin(), materials->end(), [&](const std::pair<std::string, Material>& material) {
        auto texture_file = material.second.texture_file();

        if (!texture_file.empty())
            textures_to_load.push_back(texture_file);
    });

    return textures_to_load;
}
