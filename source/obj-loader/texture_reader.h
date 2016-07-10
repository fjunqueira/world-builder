//
// Created by fabio on 4/23/16.
//

#ifndef WORLD_BUILDER_TEXTURE_READER_H
#define WORLD_BUILDER_TEXTURE_READER_H


#include <GL/glew.h>
#include <string>
#include <map>
#include <algorithm>
#include "lodepng.h"

class TextureReader
{
public:
    std::map<std::string, GLuint>* ReadTextures(const std::string& mesh_path,
                                                const std::vector<std::string>& files) const;
};


#endif //WORLD_BUILDER_TEXTURE_READER_H
