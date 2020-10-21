cmake_minimum_required(VERSION 3.0.0)
project(MathLibrary VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB_RECURSE SOURCES
    include/*.hpp
    src/*.cpp)

add_executable(MathLibrary ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
