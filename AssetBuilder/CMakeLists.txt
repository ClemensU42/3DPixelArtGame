cmake_minimum_required(VERSION 3.23)
project(AssetBuilder)

add_executable(${PROJECT_NAME} AssetBuilder.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)