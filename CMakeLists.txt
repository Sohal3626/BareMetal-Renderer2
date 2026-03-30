cmake_minimum_required(VERSION 4.0)
project(ToyRenderer2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/std:c++20)
endif()

add_executable(ToyRenderer2 main.cpp
        include/library/Geometry.h
        include/data/Mesh.h
        src/Mesh.cpp
        include/data/Material.h
        include/VertexShader.h
        include/Rasterizer.h
        include/Canvas.h
)
