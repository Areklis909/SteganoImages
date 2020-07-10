cmake_minimum_required(VERSION 3.9)

set(TARGET NotSteganoException)

include_directories(${CMAKE_SOURCE_DIR}/include)

project(${TARGET} VERSION 1.0.1 DESCRIPTION "NotSteganoException")

add_library(${TARGET} NotSteganoException.cpp)

# target_link_libraries(${TARGET}
#     opencv_imgcodecs)
