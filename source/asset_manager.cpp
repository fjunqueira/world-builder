#include "asset_manager.h"

void AssetManager::LoadAssets(const std::initializer_list<std::string>& files)
{
    ObjLoader loader;
    ObjInfo2VAO adapter;

    std::string root_path = "assets/";

    std::for_each(files.begin(), files.end(), [&](const std::string file) {

        ObjInfo obj = loader.LoadObj(root_path, file);

        VertexArrayObject vao = adapter.Adapt(obj.mesh, obj.materials, obj.textures);

        this->assets_.insert(std::pair<std::string, VertexArrayObject>(file, vao));
        
        delete obj.mesh;
        delete obj.materials;
        delete obj.textures;
    });
}

VertexArrayObject AssetManager::get_asset(const std::string& name) { return this->assets_.at(name); }