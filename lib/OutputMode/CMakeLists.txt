cmake_minimum_required(VERSION 3.9)

set(TARGET OutputMode)

include_directories(${CMAKE_SOURCE_DIR}/include)

project(${TARGET} VERSION 1.0.1 DESCRIPTION "OutputMode")

add_library(${TARGET} OutputMode.cpp)