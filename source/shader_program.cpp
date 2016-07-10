#include "shader_program.h"

ShaderProgram::ShaderProgram(const char* vertex_shader, const char* fragment_shader)
{
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertex_shader_code = this->ReadShader(vertex_shader);

    std::string fragment_shader_code = this->ReadShader(fragment_shader);

    GLint vertex_shader_result = this->CompileShader(vertex_shader_id, vertex_shader, vertex_shader_code);

    GLint fragment_shader_result = this->CompileShader(fragment_shader_id, fragment_shader, fragment_shader_code);

    GLuint program_id = glCreateProgram();

    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);

    std::cout << "Linking program" << std::endl;
    glLinkProgram(program_id);

    this->CheckProgram(program_id);

    glDetachShader(program_id, vertex_shader_id);
    glDetachShader(program_id, fragment_shader_id);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    this->program_id_ = program_id;
}

const GLuint& ShaderProgram::program_id() const { return this->program_id_; }

std::string ShaderProgram::ReadShader(const char* path) const
{
    std::string code;
    std::ifstream stream(path, std::ios::in);

    if (stream.is_open())
    {
        std::string line = "";
        while (getline(stream, line))
            code += "\n" + line;

        stream.close();
    }
    else
    {
        std::cout << "ShaderProgram: Unable to open file " << path << std::endl;
        throw std::exception();
    }

    return code;
}

GLint ShaderProgram::CompileShader(GLuint shader_id, const char* path, std::string& code) const
{
    // Compile Vertex Shader
    std::cout << "Compiling shader :" << path << std::endl;

    const char* cstring = code.c_str();

    glShaderSource(shader_id, 1, &cstring, NULL);
    glCompileShader(shader_id);

    return this->CheckShader(shader_id);
}

GLint ShaderProgram::CheckShader(GLuint shader_id) const
{
    GLint result;

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);

    GLint compilation_log_length;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &compilation_log_length);

    if (compilation_log_length > 0)
    {
        std::vector<char> error_message(compilation_log_length + 1);
        glGetShaderInfoLog(shader_id, compilation_log_length, NULL, &error_message[0]);
        std::cout << &error_message[0] << std::endl;
    }

    return result;
}

GLint ShaderProgram::CheckProgram(GLuint program_id) const
{
    GLint result;

    glGetProgramiv(program_id, GL_LINK_STATUS, &result);

    GLint compilation_log_length;
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &compilation_log_length);

    if (compilation_log_length > 0)
    {
        std::vector<char> error_message(compilation_log_length + 1);
        glGetProgramInfoLog(program_id, compilation_log_length, NULL, &error_message[0]);
        std::cout << &error_message[0] << std::endl;
    }

    return result;
}