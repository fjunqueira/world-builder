//
// Created by fabio on 4/23/16.
//

#ifndef OBJ_VIEWER_OBJ_LOADER_H
#define OBJ_VIEWER_OBJ_LOADER_H

#include "mesh.h"
#include "mtl_reader.h"
#include "obj_reader.h"

struct ObjInfo
{
    Mesh* mesh = nullptr;
    std::map<std::string, Material>* materials = nullptr;
    std::map<std::string, GLuint>* textures = nullptr;
};

class ObjLoader
{
   public:
    ObjInfo LoadObj(const std::string& obj_path, const std::string& obj_name) const;

   private:
    std::vector<std::string> GetTexturesToLoad(const std::string& obj_path, std::map<std::string, Material>* materials) const;
};

#endif  // OBJ_VIEWER_OBJ_LOADER_H
