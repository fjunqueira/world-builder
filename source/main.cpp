#include "asset_manager.h"
#include "buffer_utils.h"
#include "challenge.h"
#include "float.h"
#include "game_object.h"
#include "geodesic_sphere.h"
#include "glm/ext.hpp"
#include "glm/gtx/transform.hpp"
#include "logger.h"
#include "picker.h"
#include "planet_evaluator.h"
#include "player_input_handler.h"
#include "renderer.h"
#include "text_writter.h"
#include "world_builder.h"

using namespace std;

void ResizeHandler(GLFWwindow* window, int w, int h)
{
    if (h < 1)
        h = 1;

    glViewport(0, 0, w, h);
}

void InitializeOpenGL()
{
    glEnable(GL_DEPTH_TEST);
    glDepthRange(0.0f, 1.0f);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClearDepth(1.0);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

GLFWwindow* InitializeGlfw()
{
    if (!glfwInit())
    {
        std::cout << "ERROR: could not start GLFW3" << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    GLFWwindow* window = glfwCreateWindow(800, 600, "world-builder", NULL, NULL);

    if (!window)
    {
        std::cout << "ERROR: could not open window with GLFW3" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();
    CheckForErrors("Apparently this error is normal...");

    glfwSetWindowSizeCallback(window, ResizeHandler);

    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported " << version << std::endl;

    return window;
}

void HandleInput(GLFWwindow* window, WorldBuilder& world_builder)
{
    if (glfwGetKey(window, GLFW_KEY_E))
        world_builder.material_mode(false);

    if (glfwGetKey(window, GLFW_KEY_M))
        world_builder.material_mode(true);

    if (glfwGetKey(window, GLFW_KEY_1))
        world_builder.selected_material("grass");
    if (glfwGetKey(window, GLFW_KEY_2))
        world_builder.selected_material("water");
    if (glfwGetKey(window, GLFW_KEY_3))
        world_builder.selected_material("sand");
}

void UpdateSphereFaceVBOs(int vertex_index, const VertexArrayObject& vao, const GeodesicSphere& sphere)
{
    buffer_utils::UpdateVertexBufferObjectFace(vertex_index, vao.id(), vao.diffuse().id(),
                                               &sphere.diffuse().at(vertex_index));
    buffer_utils::UpdateVertexBufferObjectFace(vertex_index, vao.id(), vao.specular().id(),
                                               &sphere.specular().at(vertex_index));
    buffer_utils::UpdateVertexBufferObjectFace(vertex_index, vao.id(), vao.ambient().id(),
                                               &sphere.ambient().at(vertex_index));
    buffer_utils::UpdateVertexBufferObjectFace(vertex_index, vao.id(), vao.shininess().id(),
                                               &sphere.shininess().at(vertex_index));
}

void UpdateSphereVBOs(const VertexArrayObject& vao, const GeodesicSphere& sphere)
{
    buffer_utils::UpdateVertexBufferObject(vao.id(), vao.diffuse().id(), &sphere.diffuse().at(0),
                                           sphere.diffuse().size());
    buffer_utils::UpdateVertexBufferObject(vao.id(), vao.specular().id(), &sphere.specular().at(0),
                                           sphere.specular().size());
    buffer_utils::UpdateVertexBufferObject(vao.id(), vao.ambient().id(), &sphere.ambient().at(0),
                                           sphere.ambient().size());
    buffer_utils::UpdateVertexBufferObject(vao.id(), vao.shininess().id(), &sphere.shininess().at(0),
                                           sphere.shininess().size());
}

void ResetGame(bool& game_ended, VertexArrayObject& vao, GeodesicSphere& sphere, WorldBuilder& world_builder,
               vector<GameObject>& render_list, vector<Challenge>::const_iterator& current_challenge,
               const vector<Challenge>& challenges)
{
    game_ended = false;

    world_builder = WorldBuilder();

    sphere.SetMaterial(world_builder.selected_material());

    UpdateSphereVBOs(vao, sphere);

    render_list.clear();

    current_challenge = challenges.begin();
    std::advance(current_challenge, rand() % challenges.size());

    glfwSetTime(0);
}

int main(int argc, char** argv)
{
    srand(time(NULL));

    GLFWwindow* window = InitializeGlfw();

    if (window == nullptr)
        return 1;

    InitializeOpenGL();

    vector<Challenge> challenges = {
        Challenge("Earthlike planet (hint: 71% water)", 19.0f, 71.0f, 10.0f, 15.0f, 9.0f),
        Challenge("Marslike planet (hint: 100% sand)", 0.0f, 0.0f, 100.0f, 0.0f, 0),
        Challenge("Millerlike planet (hint: 100% water)", 0.0f, 100.0f, 0.0f, 0.0f, 0),
        Challenge("Habitable planet (hint: 40% water)", 30.0f, 40.0f, 30.0f, 10.0f, 20.0f),
        Challenge("Tree-only planet (hint: 100% vegetation)", 0.0f, 0.0f, 00.0f, 100.0f, 0.0f)};

    AssetManager asset_manager;
    Renderer object_renderer;
    PlayerInputHandler input_handler;
    Picker picker;
    WorldBuilder world_builder;
    PlanetEvaluator evaluator;
    TextWritter writter("fonts/Holstein.DDS");

    asset_manager.LoadAssets({"Tree8_5.obj"});

    vector<Challenge>::const_iterator current_challenge = challenges.begin();
    std::advance(current_challenge, rand() % challenges.size());

    bool game_ended = false;

    float world_radius = 1.0f;

    GeodesicSphere sphere(world_radius, 2, world_builder.selected_material());

    auto vao = buffer_utils::CreateVertexArrayObject(sphere.vertices(), sphere.normals(), sphere.ambient(),
                                                     sphere.specular(), sphere.diffuse(), sphere.shininess());

    auto picking_vao = buffer_utils::CreateFacePickingVertexArrayObject(sphere.vertices());

    GameObject sphere_object = GameObject(vao, picking_vao, glm::mat4(1.0f));

    auto tree_vao = asset_manager.get_asset("Tree8_5.obj");

    vector<GameObject> render_list;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int width, height;
        glfwGetWindowSize(window, &width, &height);

        double cursor_x, cursor_y;
        glfwGetCursorPos(window, &cursor_x, &cursor_y);

        HandleInput(window, world_builder);

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            object_renderer.RenderGameObjectForPicking(sphere_object, width, height);

            int id = picker.Pick(cursor_x, cursor_y, width, height);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if (!world_builder.IsFaceOccupied(id) && id != 0 && !game_ended)
            {
                // Only allows placing elements at the "grass" material, move to the world_builder class
                if (!world_builder.material_mode() && sphere.GetFaceDiffuse(id) == glm::vec3(0.2f, 0.5f, 0.0f))
                {
                    glm::vec3 normal = glm::vec3(sphere_object.model_matrix() * glm::vec4(sphere.GetFaceNormal(id), 0));
                    render_list.push_back(world_builder.PlaceGameElementAtFace(id, normal, world_radius, tree_vao));
                }
                else if (world_builder.material_mode())
                {
                    int vertex_index = sphere.GetVertexByFace(id);

                    sphere.SetFaceMaterial(id, world_builder.selected_material());

                    UpdateSphereFaceVBOs(vertex_index, vao, sphere);
                }
            }
        }

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
            std::for_each(render_list.begin(), render_list.end(), [&](GameObject& object) {
                input_handler.RotateObject(cursor_x, cursor_y, width, height, object);
            });

            input_handler.RotateObject(cursor_x, cursor_y, width, height, sphere_object);
        }

        std::for_each(render_list.begin(), render_list.end(),
                      [&](const GameObject& object) { object_renderer.RenderGameObject(object, width, height); });

        object_renderer.RenderGameObject(sphere_object, width, height);

        writter.PrintText(current_challenge->description_, 10, 550, 20);

        evaluator.Evaluate(sphere, world_builder);

        writter.PrintText("Grass:      " + std::to_string(evaluator.grass_percentage()), 10, 00, 20);
        writter.PrintText("Water:      " + std::to_string(evaluator.water_percentage()), 10, 20, 20);
        writter.PrintText("Sand:       " + std::to_string(evaluator.sand_percentage()), 10, 40, 20);
        writter.PrintText("Vegetation: " + std::to_string(evaluator.vegetation_percentage()), 10, 60, 20);

        if (glfwGetTime() >= 60.0f)
        {
            game_ended = true;

            if (evaluator.Succeeds(*current_challenge))
                writter.PrintText("YOU WIN", 10, 300, 22);
            else
                writter.PrintText("YOU LOSE", 10, 300, 22);

            glfwSetTime(60.0f);
        }

        char text[256];
        sprintf(text, "%.2f sec", glfwGetTime());
        writter.PrintText(text, 10, 500, 30);

        if (glfwGetKey(window, GLFW_KEY_ENTER) && game_ended)
            ResetGame(game_ended, vao, sphere, world_builder, render_list, current_challenge, challenges);

        CheckForErrors("Something went wrong...");

        glfwPollEvents();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}