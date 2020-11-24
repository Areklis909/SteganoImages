cmake_minimum_required(VERSION 3.7.2)

set(TARGET App)

include_directories(${CMAKE_SOURCE_DIR}/include)

project(${TARGET} VERSION 1.0.1)

add_library(${TARGET} App.cpp)

target_link_libraries(${TARGET} ImageHandler ImageEncryptor ImageDecoder CommandLineParser MessageTooBigException NotSteganoException ResultHandler)
