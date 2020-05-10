cmake_minimum_required(VERSION 3.9)

set(TARGET ParallelEncoder)

include_directories(${CMAKE_SOURCE_DIR}/include)

project(${TARGET} VERSION 1.0.1 DESCRIPTION "ImageHandler")

add_library(${TARGET} ParallelEncoder.cpp)

target_link_libraries(${TARGET}
    ImageHandler pthread)
