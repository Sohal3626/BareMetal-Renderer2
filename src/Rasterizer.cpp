//
// Created by Sohal03 on 26. 3. 31..
//
#include "../include/Rasterizer.h"
#include "../include/Canvas.h"
#include "../include/VertexShader.h"
#include <span>

using namespace std;

void FillTriangle(Canvas& canvas, const span<const TFVertex, 3> pts) {
    const int w = canvas.width;

    float minX = pts[0].position.x, maxX = pts[0].position.x;
    float minY = pts[0].position.y, maxY = pts[0].position.y;

    for (size_t i = 1; i < pts.size(); i++) {
        minX = min(minX, pts[i].position.x);
        minY = min(minY, pts[i].position.y);
        maxX = max(maxX, pts[i].position.x);
        maxY = max(maxY, pts[i].position.y);
    }

    const int xStart = max(0, static_cast<int>(floor(minX)));
    const int xEnd = min(canvas.width - 1, static_cast<int>(ceil(maxX)));
    const int yStart = max(0, static_cast<int>(floor(minY)));
    const int yEnd = min(canvas.height - 1, static_cast<int>(ceil(maxY)));

    const Vec2 tri[3] = {
        Vec2 {pts[0].position.x, pts[0].position.y},
        Vec2 {pts[1].position.x, pts[1].position.y},
        Vec2 {pts[2].position.x, pts[2].position.y}
    };

    for (int i = yStart; i <= yEnd; i++) {
        for (int j = xStart; j <= xEnd; j++) {
            const Vec3 bary = barycentric(Vec2{static_cast<float>(j), static_cast<float>(i)}, tri);

            float depth = pts[0].position.z * bary.x + pts[1].position.z * bary.y + pts[2].position.z * bary.z;
            if (bary.x < 0 || bary.y < 0 || bary.z < 0 || depth > canvas.depthBuffer[i * w + j]) continue;


            const Vec3 color = {bary.x, bary.y, bary.z}; // 임시값 그라데이션
            // color = 프레그먼트 셰이더 호출
            canvas.depthBuffer[i * w + j] = depth;
            canvas.setPixel(j, i, color);
        }
    }
}