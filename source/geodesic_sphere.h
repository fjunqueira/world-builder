#ifndef WORLD_BUILDER_GEODESIC_SPHERE_H
#define WORLD_BUILDER_GEODESIC_SPHERE_H

#include "glm/glm.hpp"
#include "obj-loader/material.h"
#include <GL/glew.h>
#include <vector>

const float X = .525731112119133606;
const float Z = .850650808352039932;

class GeodesicSphere
{
  public:
    GeodesicSphere(float radius, int bisections, const Material& material);

    const std::vector<glm::vec3>& vertices() const;

    const std::vector<glm::vec3>& normals() const;

    const std::vector<glm::vec3>& ambient() const;

    const std::vector<glm::vec3>& specular() const;

    const std::vector<glm::vec3>& diffuse() const;

    const std::vector<float>& shininess() const;

    int GetVertexByFace(int face_id) const;

    void SetMaterial(const Material& material);

    glm::vec3 GetFaceNormal(int face_id) const;

    void SetFaceMaterial(int face_id, const Material& material);

    glm::vec3 GetFaceDiffuse(int face_id) const;

  private:
    std::vector<glm::vec3> vertices_;
    std::vector<glm::vec3> normals_;

    std::vector<glm::vec3> ambient_;
    std::vector<glm::vec3> specular_;
    std::vector<glm::vec3> diffuse_;
    std::vector<float> shininess_;

    void SetAttributeForFace(std::vector<glm::vec3>& attribute, int face_id, const glm::vec3& value);

    void SetAttributeForFace(std::vector<float>& attribute, int face_id, const float& value);

    void Bisect(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const float& radius, int depth);

    void AddToMesh(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3);

    void AppendMeshData(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const glm::vec3& v1_normal,
                        const glm::vec3& v2_normal, const glm::vec3& v3_normal);
};

namespace Icosahedron
{
static glm::vec3 vertex_data[12] = {glm::vec3(-X, 0.0, Z), glm::vec3(X, 0.0, Z),   glm::vec3(-X, 0.0, -Z),
                                    glm::vec3(X, 0.0, -Z), glm::vec3(0.0, Z, X),   glm::vec3(0.0, Z, -X),
                                    glm::vec3(0.0, -Z, X), glm::vec3(0.0, -Z, -X), glm::vec3(Z, X, 0.0),
                                    glm::vec3(-Z, X, 0.0), glm::vec3(Z, -X, 0.0),  glm::vec3(-Z, -X, 0.0)};

static GLuint triangles[20][3] = {{0, 4, 1}, {0, 9, 4},  {9, 5, 4},  {4, 5, 8},  {4, 8, 1},  {8, 10, 1}, {8, 3, 10},
                                  {5, 3, 8}, {5, 2, 3},  {2, 7, 3},  {7, 10, 3}, {7, 6, 10}, {7, 11, 6}, {11, 0, 6},
                                  {0, 1, 6}, {6, 1, 10}, {9, 0, 11}, {9, 11, 2}, {9, 2, 5},  {7, 2, 11}};
};

#endif // WORLD_BUILDER_GEODESIC_SPHERE_H
