#include <iostream>

#include "include/Canvas.h"
#include "include/Rasterizer.h"
#include "include/Renderer.h"
#include "include/VertexShader.h"
#include "include/data/Mesh.h"

// TIP 코드를 <b>Run</b>하려면 <shortcut actionId="Run"/>을(를) 누르거나 여백에서 <icon src="AllIcons.Actions.Execute"/> 아이콘을 클릭하세요.
int main() {
    constexpr int width = 800;
    constexpr int height = 600;
    Canvas canvas(width, height);

    Mesh model;
    model.load_obj("../filname");

    // 3. 행렬 준비 (MVP)
    const Mat44 modelMat;
    const Mat44 viewMat;
    const Mat44 projectionMat =
        perspective(90.0f, static_cast<float>(width)/static_cast<float>(height), 0.1f, 100.0f);

    // 4. 버텍스 셰이더 생성
    VertexShader vShader(modelMat, viewMat, projectionMat);

    // 5. 렌더링 시작!
    DrawModel(canvas, model, vShader);

    // 6. 결과 확인
    canvas.save_ppm("test_result.ppm");

    return 0;
}