cmake_minimum_required(VERSION 3.10)
project(SummonerRift)

set(CMAKE_CXX_STANDARD 11)

# Find packages
find_package(glm REQUIRED)

# Include directories
include_directories(${GLM_INCLUDE_DIRS})

# Source files
set(SOURCES
    Camera.cpp
    Rift.cpp
    Mesh.cpp
    ShaderProgram.cpp
    Texture2D.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add tinygltf library
add_library(tinygltf ${CMAKE_CURRENT_SOURCE_DIR}/tiny_gltf.cc)

# Add executable
add_executable(SummonerRift ${SOURCES})

# Copy shader files to build directory
file(GLOB SHADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.*")
file(COPY ${SHADER_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shaders)

# Copy model files to build directory
file(GLOB MODEL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/models/*.*")
file(COPY ${MODEL_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/models)

# Copy texture files to build directory
file(GLOB TEXTURE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/textures/*.*")
file(COPY ${TEXTURE_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/textures)

# Link libraries
target_link_libraries(SummonerRift glfw GLEW GL ${GLM_LIBRARIES} tinygltf)
