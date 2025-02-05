cmake_minimum_required(VERSION 3.29)
project(dsa)

set(CMAKE_CXX_STANDARD 20)

file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})

include_directories(include)
include_directories(src)

add_executable(
        dsa main.cpp
        include/models/Stack.h
        include/SortedList.h
        include/PtrQueue.h

        src/models/Stack.cpp
        src/models/SortedList.cpp

        src/models/Account.cpp
        src/models/Actor.cpp
        src/models/Movie.cpp
        src/models/Application.cpp

        include/models/Rateable.h
        src/models/Rateable.cpp
        src/models/User.cpp
        include/models/User.h
        include/models/Admin.h
        src/models/Admin.cpp)
