cmake_minimum_required(VERSION 2.8.12)

project(SteganoImages)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GCC_COVERAGE_COMPILE_FLAGS "-O3 -Wall")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

find_library(boost_program_options_location NAMES libboost_program_options.so)
message(STATUS ${boost_program_options_location})
add_library(boost_program_options SHARED IMPORTED)
set_target_properties(boost_program_options PROPERTIES IMPORTED_LOCATION ${boost_program_options_location})


add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(external/googletest)
add_subdirectory(test)
