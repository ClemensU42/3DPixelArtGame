cmake_minimum_required(VERSION 3.23)
project(Engine VERSION 1.0)

add_subdirectory(vendor/glfw-3.3)
add_subdirectory(vendor/glm)

set(ASSET_SOURCES src/Engine/Assets/AssetManager.cpp include/Engine/Assets/AssetManager.h)
set(GRAPHICS_SOURCES src/Engine/Graphics/Mesh.cpp include/Engine/Graphics/Mesh.h src/Engine/Graphics/Shader.cpp include/Engine/Graphics/Shader.h src/Engine/Graphics/Texture.cpp include/Engine/Graphics/Texture.h)

option( TRACY_ENABLE "" ON)
option( TRACY_ON_DEMAND "" ON)
add_subdirectory (vendor/tracy)

add_library(Engine vendor/glad/src/glad.c ${ASSET_SOURCES} ${GRAPHICS_SOURCES})

target_include_directories(Engine PUBLIC vendor/glm/glm vendor/glfw-3.3/include vendor/glad/include vendor/tracy/public include)

target_link_libraries(Engine PUBLIC glfw ${CMAKE_SOURCE_DIR}/lib/assimp-vc142-mtd.lib Tracy::TracyClient)