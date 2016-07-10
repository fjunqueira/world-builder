//
// Created by fabio on 3/15/16.
//

#ifndef WORLD_BUILDER_FACE_H
#define WORLD_BUILDER_FACE_H

#include <vector>
#include <string>

class Face
{
public:
    Face(const std::string& material,
         const std::vector<int>& face_vertices,
         const std::vector<int>& face_normals,
         const std::vector<int>& face_mappings);

    const std::string& material() const;

    const std::vector<int>& vertices_indexes() const;

    const std::vector<int>& normals_indexes() const;

    const std::vector<int>& mappings_indexes() const;

private:
    std::string material_;
    std::vector<int> vertices_indexes_;
    std::vector<int> normals_indexes_;
    std::vector<int> mappings_indexes_;
};

#endif //WORLD_BUILDER_FACE_H
