//
// Created by fabio on 3/15/16.
//

#include "face.h"

Face::Face(const std::string& material,
           const std::vector<int>& face_vertices,
           const std::vector<int>& face_normals,
           const std::vector<int>& face_mappings) :
                                                material_(material),
                                                vertices_indexes_(face_vertices),
                                                normals_indexes_(face_normals),
                                                mappings_indexes_(face_mappings)
{

}

const std::vector<int>& Face::vertices_indexes() const
{
    return this->vertices_indexes_;
}

const std::vector<int>& Face::normals_indexes() const
{
    return this->normals_indexes_;
}

const std::vector<int>& Face::mappings_indexes() const
{
    return this->mappings_indexes_;
}

const std::string& Face::material() const
{
    return this->material_;
}