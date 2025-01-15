cmake_minimum_required(VERSION 3.29)
project(dsa)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(dsa main.cpp
        include/models/Account.h
        include/models/Account.h
        include/models/User.h
        include/models/User.h
        src/models/Account.cpp
        src/models/Account.cpp
        src/models/User.cpp
        include/models/Administrator.h
        src/models/Administrator.cpp
        include/models/Movie.h
        src/models/Movie.cpp
        include/models/Actor.h
        src/models/Actor.cpp
        include/models/Application.h
        src/models/Application.cpp)
