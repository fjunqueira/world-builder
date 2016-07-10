//
// Created by fabio on 4/10/16.
//

#ifndef WORLD_BUILDER_MTL_READER_H
#define WORLD_BUILDER_MTL_READER_H

#include <map>
#include <string>
#include "material.h"
#include "glm/glm.hpp"
#include <iostream>
#include <fstream>

class MtlReader
{
public:
    std::map<std::string, Material>* ReadMaterials(const std::string& file_path) const;
private:
    glm::vec3 ReadVector3(std::ifstream& file) const;
};


#endif //WORLD_BUILDER_MTL_READER_H
