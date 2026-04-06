//
// Created by desktop on 26. 3. 29..
//

#ifndef TOYRENDERER2_RASTERIZER_H
#define TOYRENDERER2_RASTERIZER_H

#include "../include/Rasterizer.h"
#include "../include/Canvas.h"
#include "../include/VertexShader.h"

void FillTriangle(Canvas& canvas, std::span<const TFVertex, 3> pts);

#endif //TOYRENDERER2_RASTERIZER_H