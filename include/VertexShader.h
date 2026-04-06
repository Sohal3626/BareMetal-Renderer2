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

class VertexShader {
public:
    Mat44 model;
    Mat44 view;
    Mat44 projection;
    Mat44 mvp;

    VertexShader(const Mat44& model, const Mat44& view, const Mat44& projection)
    : model(model), view(view), projection(projection) { mvp = projection * view * model; }

    [[nodiscard]] TFVertex vertexShader(const Vertex& in) const {
        TFVertex out;

        out.position = mvp * in.position;
        out.normal = Vec4(in.normal.x, in.normal.y, in.normal.z, 0.0f);
        out.texCoord = in.texCoord;
        out.invW = (out.position.w != 0.0f) ? (1.0f / out.position.w) : 1.0f;

        return out;
    }
};

#endif //TOYRENDERER2_VERTEXSHADER_H