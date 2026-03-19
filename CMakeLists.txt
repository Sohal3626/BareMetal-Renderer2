cmake_minimum_required(VERSION 4.0)
project(ToyRenderer2)

set(CMAKE_CXX_STANDARD 20)

add_executable(ToyRenderer2 main.cpp
        include/library/Geometry.h
        include/data/Mesh.h
        src/Mesh.cpp
        include/data/Material.h
        include/Core.h
)
