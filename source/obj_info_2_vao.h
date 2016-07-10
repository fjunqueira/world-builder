#ifndef WORLD_BUILDER_OBJ_INFO_2_VAO_H
#define WORLD_BUILDER_OBJ_INFO_2_VAO_H

#include <GL/glew.h>
#include "buffer_utils.h"
#include "obj-loader/obj_loader.h"

class ObjInfo2VAO
{
  public:
    VertexArrayObject Adapt(Mesh* mesh, std::map<std::string, Material>* materials,
                            std::map<std::string, GLuint>* textures);

  private:
    void QuadToTriangle(std::vector<int>& data);
};

#endif // WORLD_BUILDER_OBJ_INFO_2_VAO_H