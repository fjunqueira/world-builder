#ifndef WORLD_BUILDER_ASSET_MANAGER_H
#define WORLD_BUILDER_ASSET_MANAGER_H

#include <initializer_list>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "obj-loader/obj_loader.h"
#include "obj_info_2_vao.h"

class AssetManager
{
   public:
    void LoadAssets(const std::initializer_list<std::string>& paths);

    VertexArrayObject get_asset(const std::string&);

   private:
    std::unordered_map<std::string, VertexArrayObject> assets_;
};

#endif  // WORLD_BUILDER_ASSET_MANAGER_H