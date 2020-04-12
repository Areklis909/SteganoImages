cmake_minimum_required(VERSION 3.9)

set(TARGET TextToBitsConverter)

include_directories(${CMAKE_SOURCE_DIR}/include)

project(${TARGET} VERSION 1.0.1 DESCRIPTION "TextToBitsConverter")

add_library(${TARGET} TextToBitsConverter.cpp)

#target_link_libraries(${TARGET})
