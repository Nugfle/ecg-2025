cmake_minimum_required(VERSION 3.15...4.0)

project(Trees VERSION 1.0 DESCRIPTION "A Tree like Datastructure" LANGUAGES CXX)

add_library(tree STATIC lib/node.h lib/node.cpp)
target_include_directories(tree PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

add_executable(ecg_tree main.cpp)

target_link_libraries(ecg_tree PRIVATE tree)
