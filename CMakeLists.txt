cmake_minimum_required(VERSION 3.22)
project(scrabble)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

if(WIN32)
    set(CMAKE_EXECUTABLE_SUFFIX ".exe")
else()
    set(CMAKE_EXECUTABLE_SUFFIX ".out")
endif()

include_directories(src)
add_subdirectory(src)