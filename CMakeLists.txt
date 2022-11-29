cmake_minimum_required(VERSION 3.23)
project(PixelArt3DGame)

set(CMAKE_CXX_STANDARD 14)

set(ASSET_FILE ${CMAKE_BINARY_DIR}\\assets.asset)

add_subdirectory(vendor/glfw-3.3.8)
add_subdirectory(vendor/glm)

option( TRACY_ENABLE "" ON)
option( TRACY_ON_DEMAND "" ON)
add_subdirectory (vendor/tracy)

set(SOURCES main.cpp vendor/glad/src/glad.c src/Application.cpp include/Application.h src/Engine/Graphics/Mesh.cpp include/Engine/Graphics/Mesh.h include/Engine/Graphics/Shader.h src/Engine/Graphics/Shader.cpp src/Engine/Assets/AssetManager.cpp include/Engine/Assets/AssetManager.h)

add_executable(PixelArt3DGame WIN32 ${SOURCES} ${TRACY_SOURCES})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_SOURCE_DIR}/AssetBuilder/cmake-build-debug/AssetBuilder.exe
        ARGS ${ASSET_FILE} ${CMAKE_SOURCE_DIR}\\Assets)

target_include_directories(${PROJECT_NAME} PUBLIC vendor/glm/glm vendor/glfw-3.3.8/include vendor/glad/include vendor/tracy/public include)

target_link_libraries(${PROJECT_NAME} glfw ${CMAKE_SOURCE_DIR}/lib/assimp-vc142-mtd.lib Tracy::TracyClient)