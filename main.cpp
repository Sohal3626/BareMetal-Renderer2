#include <iostream>
#include <ranges>

#include "include/Canvas.h"
#include "include/Rasterizer.h"
#include "include/Renderer.h"
#include "include/VertexShader.h"
#include "include/data/Mesh.h"
#include "include/library/Geometry.h"

// TIP 코드를 <b>Run</b>하려면 <shortcut actionId="Run"/>을(를) 누르거나 여백에서 <icon src="AllIcons.Actions.Execute"/> 아이콘을 클릭하세요.
int main() {
    constexpr int width = 300;
    constexpr int height = 400;
    Canvas canvas(width, height);

    Mesh model;
    model.load_obj("../obj/mymodel.obj");

    // 3. 행렬 준비
    Mat44 modelMat;
    translate(modelMat, 0, 0, 0);
    rotate (modelMat, 0, 0, 0);

    Mat44 viewMat;

    translate(viewMat, 0, 0, -3.f);
    const Mat44 projectionMat =
        perspective(45.0f, static_cast<float>(width)/static_cast<float>(height), 0.1f, 1000.0f);

    // 4. 버텍스 셰이더 생성
    const VertexShader vShader(modelMat, viewMat, projectionMat);

    // 5. 렌더링 시작
    DrawModel(canvas, model, vShader);

    // 6. 결과 확인
    canvas.save_ppm("test_result.ppm");

    return 0;
}