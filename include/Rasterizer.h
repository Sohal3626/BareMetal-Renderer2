//
// Created by desktop on 26. 3. 29..
//

#ifndef TOYRENDERER2_RASTERIZER_H
#define TOYRENDERER2_RASTERIZER_H
#include "VertexShader.h"
#include <span>

#include "Canvas.h"

void FillTriangle(const Canvas& canvas, const std::span<const TFVertex, 3> pts) {
    float minX = pts[0].position.x, maxX = pts[0].position.x;
    float minY = pts[0].position.y, maxY = pts[0].position.y;

    for (size_t i = 1; i < pts.size(); i++) {
        minX = std::min(minX, pts[i].position.x);
        minY = std::min(minY, pts[i].position.y);
        maxX = std::max(maxX, pts[i].position.x);
        maxY = std::max(maxY, pts[i].position.y);
    }

    int xStart = std::max(0, static_cast<int>(floor(minX)));
    int xEnd = std::min(canvas.width - 1, static_cast<int>(ceil(maxX)));
    int yStart = std::max(0, static_cast<int>(floor(minY)));
    int yEnd = std::min(canvas.height - 1, static_cast<int>(ceil(maxY)));

    for (int i = yStart; i < yEnd; i++) {
        for (int j = xStart; j < xEnd; j++) {
            // TODO
        }
    }


}

#endif //TOYRENDERER2_RASTERIZER_H