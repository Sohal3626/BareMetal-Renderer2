//
// Created by desktop on 26. 3. 23..
//

#ifndef TOYRENDERER2_VERTEXSHADER_H
#define TOYRENDERER2_VERTEXSHADER_H
#include "data/Mesh.h"
#include "library/Geometry.h"

struct TFVertex {
    Vec4 position;
    Vec2 texCoord;
    Vec4 normal;
    float invW{};
};

class Shader {
public:
    Mat44 model;
    Mat44 view;
    Mat44 projection;
    Mat44 mvp;

    void MVP() {
        mvp = projection * view  * model;
    }

    [[nodiscard]] TFVertex VertexShader(const Vertex& in, int width, int height) const {
        TFVertex out;

        Vec4 world = mvp * in.position;

        float invW = 1;
        if (world.w != 0) invW =  1 / world.w;
        Vec4 ndcP = world * invW;

        out.position.x = (ndcP.x + 1.f) * 0.5f * static_cast<float>(width);
        out.position.y = (1.f - ndcP.y) * 0.5f * static_cast<float>(height);
        out.position.z = ndcP.z;
        out.position.w = world.w;
        out.invW = invW;

        out.normal = {model * in.normal};

        out.texCoord = in.texCoord;

        return out;
    }
};

#endif //TOYRENDERER2_VERTEXSHADER_H