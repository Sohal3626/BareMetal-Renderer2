cmake_minimum_required(VERSION 3.20)
project(ToyRenderer2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (APPLE)
    set(OpenMP_ROOT "/opt/homebrew/opt/libomp")
    set(OpenMP_C_FLAGS "-Xpreprocessor -fopenmp -I${OpenMP_ROOT}/include")
    set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp -I${OpenMP_ROOT}/include")
    set(OpenMP_C_LIB_NAMES "omp")
    set(OpenMP_CXX_LIB_NAMES "omp")
    set(OpenMP_omp_LIBRARY "${OpenMP_ROOT}/lib/libomp.dylib")
elseif(WIN32 AND NOT MSVC)
    set(OpenMP_CXX_FLAGS "-fopenmp")
    set(OpenMP_C_FLAGS "-fopenmp")
endif()

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
        src/Material.cpp
)

if(OpenMP_CXX_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)

    if(WIN32 AND NOT MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE -fopenmp)
        target_link_options(${PROJECT_NAME} PRIVATE -fopenmp)
    endif()

    if(APPLE)
        target_include_directories(${PROJECT_NAME} PRIVATE "/opt/homebrew/opt/libomp/include")
    endif()
endif()

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /O2 /Oi /Ot /EHsc /openmp)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -O3 -march=native)
endif()