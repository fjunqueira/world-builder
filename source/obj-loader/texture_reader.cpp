//
// Created by fabio on 4/23/16.
//

#include "texture_reader.h"

std::map<std::string, GLuint>* TextureReader::ReadTextures(const std::string& mesh_path,
                                                           const std::vector<std::string>& files) const
{
    std::map<std::string, GLuint>* textures = new std::map<std::string, GLuint>();

    GLuint* texture_ids = new GLuint[files.size()]();

    glGenTextures((GLsizei) files.size(), texture_ids);

    std::for_each(files.begin(), files.end(), [&](const std::string& file)
    {

        GLuint textureid = *texture_ids++;

        std::vector<unsigned char> image;

        unsigned int width, height;

        lodepng::decode(image, width, height, mesh_path + file);

        glBindTexture(GL_TEXTURE_2D, textureid);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, &image[0]);

        textures->insert(std::pair<std::string, GLuint>(file, textureid));
    });

    delete[] (texture_ids - files.size());
    return textures;
}