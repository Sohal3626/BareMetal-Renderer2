//
// Created by desktop on 26. 3. 29..
//

#ifndef TOYRENDERER2_RASTERIZER_H
#define TOYRENDERER2_RASTERIZER_H
#include "VertexShader.h"
#include <span>

#include "Canvas.h"

static void FillTriangle(Canvas& canvas, const std::span<const TFVertex, 3> pts) {
    float minX = pts[0].position.x, maxX = pts[0].position.x;
    float minY = pts[0].position.y, maxY = pts[0].position.y;

    for (size_t i = 1; i < pts.size(); i++) {
        minX = std::min(minX, pts[i].position.x);
        minY = std::min(minY, pts[i].position.y);
        maxX = std::max(maxX, pts[i].position.x);
        maxY = std::max(maxY, pts[i].position.y);
    }

    const int xStart = std::max(0, static_cast<int>(floor(minX)));
    const int xEnd = std::min(canvas.width - 1, static_cast<int>(ceil(maxX)));
    const int yStart = std::max(0, static_cast<int>(floor(minY)));
    const int yEnd = std::min(canvas.height - 1, static_cast<int>(ceil(maxY)));

    const Vec2 tri[3] = {
        Vec2 {pts[0].position.x, pts[0].position.y},
        Vec2 {pts[1].position.x, pts[1].position.y},
        Vec2 {pts[2].position.x, pts[2].position.y}
    };

    for (int i = yStart; i <= yEnd; i++) {
        for (int j = xStart; j <= xEnd; j++) {
            const Vec3 bary = barycentric(Vec2{static_cast<float>(j), static_cast<float>(i)}, tri);

            if (bary.x < 0 || bary.y < 0 || bary.z < 0) continue;

            const Vec3 color = {bary.x, bary.y, bary.z}; // 임시값 그라데이션
            // color = 프레그먼트 셰이더 호출
            canvas.setPixel(j, i, color);
        }
    }
}

#endif //TOYRENDERER2_RASTERIZER_H