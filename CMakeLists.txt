cmake_minimum_required(VERSION 3.23)
project(PixelArt3DGame)

set(CMAKE_CXX_STANDARD 14)

set(ASSET_FILE ${CMAKE_BINARY_DIR}\\assets.asset)

add_subdirectory(Engine)

set(SOURCES main.cpp  src/Application.cpp include/Application.h)

add_custom_target(asset_target
        COMMAND ${CMAKE_SOURCE_DIR}/AssetBuilder/cmake-build-debug/AssetBuilder.exe ${ASSET_FILE} ${CMAKE_SOURCE_DIR}\\Assets)

add_executable(PixelArt3DGame WIN32 ${SOURCES})

add_dependencies(${PROJECT_NAME} asset_target)

target_include_directories(${PROJECT_NAME} PUBLIC Engine/include include)

target_link_libraries(${PROJECT_NAME} PUBLIC Engine)