#include "logger.h"

void CheckForErrors(const std::string& log_message)
{
    GLuint error = glGetError();

    if (error != GL_NO_ERROR)
    {
        std::cout << log_message << error << std::endl;
    }
}