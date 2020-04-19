cmake_minimum_required(VERSION 3.9)

set(TARGET ImageEncryptor)

include_directories(${CMAKE_SOURCE_DIR}/include)

project(${TARGET} VERSION 1.0.1 DESCRIPTION "ImageEncryptor")

add_library(${TARGET} ImageEncryptor.cpp)

target_link_libraries(${TARGET}
    ImageHandler TextToBitsConverter CharBit)