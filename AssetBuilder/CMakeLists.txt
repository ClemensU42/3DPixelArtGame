cmake_minimum_required(VERSION 3.23)
project(AssetBuilder)

find_library(ASSIMP assimp)

add_executable(${PROJECT_NAME} AssetBuilder.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/assimp-vc142-mtd.lib)