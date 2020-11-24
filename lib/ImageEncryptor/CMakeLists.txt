cmake_minimum_required(VERSION 3.7.2)

set(TARGET ImageEncryptor)

include_directories(${CMAKE_SOURCE_DIR}/include)

project(${TARGET} VERSION 1.0.1)

add_library(${TARGET} ImageEncryptorInterface.cpp ImageEncryptorFactory.cpp MultiImageEncryptor.cpp SingleImageEncryptor.cpp ImageEncryptorManager.cpp)

target_link_libraries(${TARGET}
    ImageHandler ParallelEncoder Utils)