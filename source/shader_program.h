#ifndef WORLD_BUILDER_SHADER_PROGRAM_H
#define WORLD_BUILDER_SHADER_PROGRAM_H

#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class ShaderProgram
{
  public:
    ShaderProgram(const char* vertex_shader, const char* fragment_shader);
    
    const GLuint& program_id() const;
  
  private:
    GLuint program_id_;

    std::string ReadShader(const char* path) const;

    GLint CompileShader(GLuint shader_id, const char* path, std::string& code) const;

    GLint CheckShader(GLuint id) const;

    GLint CheckProgram(GLuint id) const;
};

#endif // WORLD_BUILDER_SHADER_PROGRAM_H