#include "geodesic_sphere.h"

GeodesicSphere::GeodesicSphere(float radius, int bisections, const Material& material)
{
    for (int i = 0; i < 20; i++)
    {
        this->Bisect(Icosahedron::vertex_data[Icosahedron::triangles[i][0]],
                     Icosahedron::vertex_data[Icosahedron::triangles[i][1]],
                     Icosahedron::vertex_data[Icosahedron::triangles[i][2]], radius, bisections);
    }

    for (int i = 0; i < this->vertices_.size(); i++)
    {
        ambient_.push_back(material.ambient());
        specular_.push_back(material.specular());
        diffuse_.push_back(material.diffuse());
        shininess_.push_back(material.shininess());
    }
}

void GeodesicSphere::SetMaterial(const Material& material)
{
    for (int i = 0; i < this->vertices_.size(); i++)
    {
        ambient_.at(i) = material.ambient();
        specular_.at(i) = material.specular();
        diffuse_.at(i) = material.diffuse();
        shininess_.at(i) = material.shininess();
    }
}

glm::vec3 GeodesicSphere::GetFaceNormal(int face_id) const
{
    int vertex_index = this->GetVertexByFace(face_id);

    glm::vec3 normal_1 = this->normals_.at(vertex_index);
    glm::vec3 normal_2 = this->normals_.at(vertex_index + 1);
    glm::vec3 normal_3 = this->normals_.at(vertex_index + 2);

    return normal_1 + normal_2 + normal_3;
}

glm::vec3 GeodesicSphere::GetFaceDiffuse(int face_id) const
{
    return this->diffuse_.at(this->GetVertexByFace(face_id));
}

void GeodesicSphere::SetFaceMaterial(int face_id, const Material& material)
{
    int vertex_index = this->GetVertexByFace(face_id);

    this->SetAttributeForFace(this->ambient_, vertex_index, material.ambient());
    this->SetAttributeForFace(this->specular_, vertex_index, material.specular());
    this->SetAttributeForFace(this->diffuse_, vertex_index, material.diffuse());
    this->SetAttributeForFace(this->shininess_, vertex_index, material.shininess());
}

void GeodesicSphere::SetAttributeForFace(std::vector<glm::vec3>& attribute, int face_id, const glm::vec3& value)
{
    attribute.at(face_id) = value;
    attribute.at(face_id + 1) = value;
    attribute.at(face_id + 2) = value;
}

void GeodesicSphere::SetAttributeForFace(std::vector<float>& attribute, int face_id, const float& value)
{
    attribute.at(face_id) = value;
    attribute.at(face_id + 1) = value;
    attribute.at(face_id + 2) = value;
}

int GeodesicSphere::GetVertexByFace(int face_id) const { return (face_id - 1) * 3; }

const std::vector<glm::vec3>& GeodesicSphere::vertices() const { return this->vertices_; }

const std::vector<glm::vec3>& GeodesicSphere::normals() const { return this->normals_; }

const std::vector<glm::vec3>& GeodesicSphere::ambient() const { return this->ambient_; }

const std::vector<glm::vec3>& GeodesicSphere::specular() const { return this->specular_; }

const std::vector<glm::vec3>& GeodesicSphere::diffuse() const { return this->diffuse_; }

const std::vector<float>& GeodesicSphere::shininess() const { return this->shininess_; }

void GeodesicSphere::Bisect(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const float& radius,
                            int depth)
{
    if (depth == 0)
    {
        this->AddToMesh(v1 * (float)radius, v2 * (float)radius, v3 * (float)radius);
        return;
    }

    glm::vec3 v12 = glm::normalize(v1 + v2);
    glm::vec3 v23 = glm::normalize(v2 + v3);
    glm::vec3 v31 = glm::normalize(v3 + v1);

    this->Bisect(v1, v12, v31, radius, depth - 1);
    this->Bisect(v2, v23, v12, radius, depth - 1);
    this->Bisect(v3, v31, v23, radius, depth - 1);
    this->Bisect(v12, v23, v31, radius, depth - 1);
}

void GeodesicSphere::AddToMesh(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3)
{
    glm::vec3 v1_normal = glm::normalize(glm::cross((v3 - v1), (v2 - v1)));
    glm::vec3 v2_normal = glm::normalize(glm::cross((v1 - v2), (v3 - v2)));
    glm::vec3 v3_normal = glm::normalize(glm::cross((v2 - v3), (v1 - v3)));

    this->AppendMeshData(v3, v2, v1, v3_normal, v2_normal, v1_normal);
}

void GeodesicSphere::AppendMeshData(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3,
                                    const glm::vec3& v1_normal, const glm::vec3& v2_normal, const glm::vec3& v3_normal)
{
    this->normals_.push_back(v1_normal);
    this->vertices_.push_back(v1);

    this->normals_.push_back(v2_normal);
    this->vertices_.push_back(v2);

    this->normals_.push_back(v3_normal);
    this->vertices_.push_back(v3);
}