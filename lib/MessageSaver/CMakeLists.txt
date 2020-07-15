cmake_minimum_required(VERSION 3.9)

set(TARGET MessageSaver)

include_directories(${CMAKE_SOURCE_DIR}/include)

project(${TARGET} VERSION 1.0.1 DESCRIPTION "MessageSaver")

add_library(${TARGET} MessageSaver.cpp)

# target_link_libraries(${TARGET})
