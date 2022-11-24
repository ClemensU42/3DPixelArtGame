cmake_minimum_required(VERSION 3.23)
project(PixelArt3DGame)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(vendor/glfw-3.3.8)
add_subdirectory(vendor/glm)

set(SOURCES main.cpp vendor/glad/src/glad.c src/Application.cpp include/Application.h src/Engine/Graphics/Mesh.cpp include/Engine/Graphics/Mesh.h include/Engine/Graphics/Shader.h src/Engine/Graphics/Shader.cpp)

add_executable(PixelArt3DGame WIN32 ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC vendor/glm/glm vendor/glfw-3.3.8/include vendor/glad/include include)

target_link_libraries(${PROJECT_NAME} glfw ${CMAKE_SOURCE_DIR}/lib/assimp-vc142-mtd.lib)