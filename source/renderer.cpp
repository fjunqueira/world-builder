#include "renderer.h"

Renderer::Renderer()
    : game_object_program_("shaders/vertex.glsl", "shaders/fragment.glsl"),
      game_object_picking_program_("shaders/vertex.glsl", "shaders/fragment_picking.glsl")
{
}

// DO I NEED THE GAMEOBJECT CLASS?
void Renderer::RenderGameObject(const GameObject& game_object, int width, int height) const
{
    auto shader_id = this->game_object_program_.program_id();

    glUseProgram(shader_id);

    this->Render(shader_id, game_object, width, height);

    GLuint light_location = glGetUniformLocation(shader_id, "LightPosition_worldspace");

    glm::vec3 lightPos = glm::vec3(0.0f, 11.0f, 0.0f);
    glUniform3f(light_location, lightPos.x, lightPos.y, lightPos.z);

    auto vao = game_object.vao();

    glBindVertexArray(vao.id());

    glDrawArrays(GL_TRIANGLES, 0, vao.vertices().size());
}

void Renderer::RenderGameObjectForPicking(const GameObject& game_object, int width, int height) const
{
    auto shader_id = this->game_object_picking_program_.program_id();
    
    glUseProgram(shader_id);
    
    this->Render(shader_id, game_object, width, height);
    
    auto vao = game_object.picking_vao();

    glBindVertexArray(vao.id());
    
    glDrawArrays(GL_TRIANGLES, 0, vao.vertices().size());
}

void Renderer::Render(GLuint program_id, const GameObject& game_object, int width, int height) const
{
    GLuint matrix_location = glGetUniformLocation(program_id, "MVP");    
    GLuint view_matrix_location = glGetUniformLocation(program_id, "V"); 
    GLuint model_matrix_location = glGetUniformLocation(program_id, "M");

    // Projection matrix : 45 degrees Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

    // Camera matrix
    glm::mat4 view_matrix = glm::lookAt(glm::vec3(0.0, 5.0, 0.0f), // Camera is here
                                        glm::vec3(0, 0, 0),  // and looks here : at the same position, plus "direction"
                                        glm::vec3(0, 0, 1)); // Head is up (set to 0,-1,0 to look upside-down)
    // World matrix
    glm::mat4 model_matrix = game_object.model_matrix();

    glm::mat4 mvp = projection_matrix * view_matrix * model_matrix;

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glUniformMatrix4fv(matrix_location, 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, &view_matrix[0][0]);
    glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, &model_matrix[0][0]);
}

const ShaderProgram& Renderer::game_object_program() const { return this->game_object_program_; }

const ShaderProgram& Renderer::game_object_picking_program() const { return this->game_object_picking_program_; }