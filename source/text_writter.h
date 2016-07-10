#ifndef WORLD_BUILDER_TEXT_WRITTER_H
#define WORLD_BUILDER_TEXT_WRITTER_H

#include "glm/glm.hpp"
#include "shader_program.h"
#include <GL/glew.h>
#include <string.h>
#include <vector>

class TextWritter
{
  public:
    TextWritter(const char* texturePath);
    void PrintText(const std::string& text, int x, int y, int size);
    void CleanupText();
    GLuint LoadDDS(const char* imagepath);

  private:
    unsigned int Text2DVertexArrayID;
    unsigned int Text2DTextureID;
    unsigned int Text2DVertexBufferID;
    unsigned int Text2DUVBufferID;
    unsigned int Text2DShaderID;
    unsigned int Text2DUniformID;
};

#endif // WORLD_BUILDER_TEXT_WRITTER_H