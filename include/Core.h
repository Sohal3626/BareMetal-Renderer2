//
// Created by desktop on 26. 3. 19..
//

#ifndef TOYRENDERER2_CORE_H
#define TOYRENDERER2_CORE_H
#include <cstdint>
#include <vector>

class BareMetal_Renderer {
public:
    // 1. 상태 설정 (State Setting)
    void SetVertexBuffer(const std::vector<Vertex>& vb);
    void SetIndexBuffer(const std::vector<uint32_t>& ib);
    void SetShader(IShader* shader);
    void SetTexture(Texture* tex);

    // 2. 실행 (The Draw Call)
    void DrawIndexed(uint32_t count);

private:
    // 실제 내부 로직 (Rasterization, Clipping 등)
    void ProcessVertex();
    void RasterizeTriangle();
};

#endif //TOYRENDERER2_CORE_H