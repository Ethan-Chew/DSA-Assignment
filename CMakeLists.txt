cmake_minimum_required(VERSION 3.29)
project(dsa)

set(CMAKE_CXX_STANDARD 20)

file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})

include_directories(include)
include_directories(src)

add_executable(dsa main.cpp)