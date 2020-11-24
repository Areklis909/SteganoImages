cmake_minimum_required(VERSION 3.10)

set(TARGET stegano)
set(LIB_LIST App)

add_executable(${TARGET} main.cpp)

target_link_libraries(${TARGET} ${LIB_LIST})

