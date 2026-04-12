cmake_minimum_required(VERSION 3.20)
project(ToyRenderer2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenMP REQUIRED)

add_executable(ToyRenderer2
        main.cpp
        src/Mesh.cpp
        src/Rasterizer.cpp
        include/library/Geometry.h
        include/data/Mesh.h
        include/data/Material.h
        include/VertexShader.h
        include/Rasterizer.h
        include/Canvas.h
        include/Renderer.h
)

if(OpenMP_CXX_FOUND)
    target_link_libraries(ToyRenderer2 PRIVATE OpenMP::OpenMP_CXX)
    target_link_options(ToyRenderer2 PRIVATE ${OpenMP_CXX_FLAGS})
endif()

if(MSVC)
    target_compile_options(ToyRenderer2 PRIVATE /O2 /Oi /Ot /EHsc /openmp)
else()
    target_compile_options(ToyRenderer2 PRIVATE -O3 -march=native -fopenmp)
    target_link_libraries(ToyRenderer2 PRIVATE -fopenmp)
endif()