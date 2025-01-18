cmake_minimum_required(VERSION 3.29)
project(dsa)

set(CMAKE_CXX_STANDARD 20)

file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})

include_directories(include)
include_directories(src)

add_executable(dsa main.cpp
        src/models/Application.cpp
        src/models/Actor.cpp
        src/models/Movie.cpp
        src/DoubleLinkedList.cpp
        include/models/Stack.h
        src/models/Stack.cpp
        include/models/Administrator.h
        include/SortedList.h
        src/models/Account.cpp
        src/models/SortedList.cpp
        src/models/BasicFeatures.cpp
        include/BasicFeatures.h)