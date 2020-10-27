set(BINARY ${CMAKE_PROJECT_NAME}_test)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.hpp *.cpp)

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

set(LIBS CommandLineParser ImageEncryptor)

target_link_libraries(${BINARY} PUBLIC ${LIBS} gtest)
