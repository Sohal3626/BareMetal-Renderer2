//
// Created by desktop on 26. 4. 6..
//

#ifndef TOYRENDERER2_RENDERER_H
#define TOYRENDERER2_RENDERER_H
#include "Canvas.h"
#include "Rasterizer.h"
#include "VertexShader.h"
#include "data/Mesh.h"
#include "library/Geometry.h"
#include <omp.h>
#include <chrono>

inline void DrawModel(Canvas &canvas, const Mesh &mesh, const VertexShader &vertexShader) {
    std::cout << "Indices Size: " << mesh.indices.size() << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    const int w = canvas.width;
    const int h = canvas.height;

    #pragma omp parallel for schedule(dynamic, 100)
    for (size_t i = 0; i < mesh.indices.size(); i+=3) {
        TFVertex tri[3];
        for (size_t j = 0; j < 3; j++) {
            const uint32_t vertexIndex = mesh.indices[i + j];
            const Vertex& v = mesh.vertices[vertexIndex];
            //std::cout << v.position.x << " " << v.position.y << " " << v.position.z << std::endl;

            tri[j] = vertexShader.vertexShader(v);

            const float invW = tri[j].invW;
            tri[j].position.x = (tri[j].position.x * invW + 1.0f) * 0.5f * static_cast<float>(w);
            tri[j].position.y = (1.0f - tri[j].position.y * invW) * 0.5f * static_cast<float>(h);
            //std::cout << tri[j].position.x << ' ' << tri[j].position.y << std::endl;
        }
        FillTriangle(canvas, tri);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Rendering Time: " << elapsed.count() << " ms" << std::endl;
}

#endif //TOYRENDERER2_RENDERER_H