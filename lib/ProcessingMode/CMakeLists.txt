cmake_minimum_required(VERSION 3.9)

set(TARGET ProcessingMode)

include_directories(${CMAKE_SOURCE_DIR}/include)

project(${TARGET} VERSION 1.0.1 DESCRIPTION "ProcessingMode")

add_library(${TARGET} ProcessingMode.cpp)