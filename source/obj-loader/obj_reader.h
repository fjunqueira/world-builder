//
// Created by fabio on 3/15/16.
//

#ifndef WORLD_BUILDER_OBJ_READER_H
#define WORLD_BUILDER_OBJ_READER_H


#include "mesh.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "glm/glm.hpp"
#include "face.h"
#include "group.h"
#include <regex>
#include <map>

class ObjReader
{
public:
    Mesh* ReadMesh(const std::string& file_path) const;

private:
    glm::vec3 ReadVector3(std::ifstream& file) const;

    glm::vec3 ReadVector2(std::ifstream& file) const;

    Face ReadFace(std::ifstream& file, const std::string& material) const;
};


#endif //WORLD_BUILDER_OBJ_READER_H
