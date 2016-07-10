//
// Created by fabio on 3/15/16.
//

#ifndef WORLD_BUILDER_GROUP_H
#define WORLD_BUILDER_GROUP_H

#include <GL/glew.h>
#include <string>
#include <vector>
#include "group.h"
#include "face.h"

class Group
{
public:
    Group(const std::string& name);

    const std::string& name() const;

    const std::vector<Face>& faces() const;

    const GLuint& group_id() const;

    void add_face(const Face& face);

private:
    std::string name_;
    std::vector<Face> faces_;
    GLuint group_id_;
};


#endif //WORLD_BUILDER_GROUP_H
