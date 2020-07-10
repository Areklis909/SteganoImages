cmake_minimum_required(VERSION 3.9)

set(TARGET ImageDecoder)

include_directories(${CMAKE_SOURCE_DIR}/include)

project(${TARGET} VERSION 1.0.1 DESCRIPTION "ImageDecoder")

add_library(${TARGET} ImageDecoder.cpp)

target_link_libraries(${TARGET}
    ImageHandler NotSteganoException)