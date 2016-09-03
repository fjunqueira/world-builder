cmake_minimum_required(VERSION 3.3)
project(world-builder)

#set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include(ExternalProject)

# Set default ExternalProject root directory
set_directory_properties(PROPERTIES EP_PREFIX ${PROJECT_SOURCE_DIR}/libs)

ExternalProject_Add(
    GLM
    DOWNLOAD_DIR ${PROJECT_SOURCE_DIR}/libs/download
    URL "https://github.com/g-truc/glm/archive/0.9.7.5.tar.gz"
    URL_HASH SHA1=d0ebd8381df187eee65599e213908b82627d7415
    CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${PROJECT_SOURCE_DIR}/libs/glm"
)

set(GLM_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/libs/glm/include)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

set(SOURCE_FILES
        source/main.cpp
        source/geodesic_sphere.cpp 
        source/geodesic_sphere.h
        source/buffer_utils.h
        source/buffer_utils.cpp
        source/renderer.h
        source/renderer.cpp
        source/game_object.h
        source/game_object.cpp
        source/shader_program.h
        source/shader_program.cpp
        source/player_input_handler.h
        source/player_input_handler.cpp
        source/picker.h
        source/picker.cpp
        source/asset_manager.h
        source/asset_manager.cpp        
        source/obj_info_2_vao.h
        source/obj_info_2_vao.cpp        
        source/world_builder.h
        source/world_builder.cpp
        source/text_writter.h
        source/text_writter.cpp
        source/planet_evaluator.h
        source/planet_evaluator.cpp
        source/logger.h
        source/logger.cpp
        source/challenge.h
        
        source/obj-loader/obj_reader.cpp
        source/obj-loader/obj_reader.h
        source/obj-loader/material.cpp
        source/obj-loader/material.h
        source/obj-loader/mesh.cpp
        source/obj-loader/mesh.h
        source/obj-loader/group.cpp
        source/obj-loader/group.h
        source/obj-loader/face.cpp
        source/obj-loader/face.h
        source/obj-loader/mtl_reader.cpp
        source/obj-loader/mtl_reader.h
        source/obj-loader/obj_loader.cpp
        source/obj-loader/obj_loader.h )

add_executable(world-builder ${SOURCE_FILES})

add_dependencies(world-builder GLM)

target_link_libraries(world-builder glfw ${GLM_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES}) 

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${CMAKE_SOURCE_DIR}/fonts DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})