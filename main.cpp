#include <iostream>
#include <ranges>


#include "include/Canvas.h"
#include "include/Renderer.h"
#include "include/VertexShader.h"
#include "include/data/Mesh.h"
#include "include/library/Geometry.h"
#include "include/Fragment/PhongShader.h"
#include "include/Fragment/BlinnPhongShader.h"
#include "include/Fragment/CelShader.h"
#include "include/Fragment/FlatShader.h"
#include "include/Fragment/UnlitShader.h"

// TIP 코드를 <b>Run</b>하려면 <shortcut actionId="Run"/>을(를) 누르거나 여백에서 <icon src="AllIcons.Actions.Execute"/> 아이콘을 클릭하세요.
int main() {
    constexpr int width = 1920;
    constexpr int height = 1080;
    Canvas canvas(width, height);
    Canvas canvas2(width, height);
    Canvas canvas3(width, height);

    Mesh model;
    model.loadObj("../obj/Miyu.obj");

    Material mtl;
    mtl.loadMtl("../mtl/miyu.mtl");

    // 3. 행렬 준비
    Mat44 modelMat;
    translate(modelMat, 0, -0.0, -2.0);
    rotate (modelMat, 0.0, 0.0, 0);

    Mat44 viewMat;

    translate(viewMat, 0, -0.8f, -1.f);
    const Mat44 projectionMat =
        perspective(45.0f, static_cast<float>(width)/static_cast<float>(height), 0.1f, 1000.0f);

    // 4. 버텍스 셰이더 생성
    const VertexShader vShader(modelMat, viewMat, projectionMat);

    // 5. 테스트
    DrawModel<FlatShader>(canvas, model, mtl, vShader, Vec3{0, 1.5, 3});
    canvas.save_ppm("test_result.ppm");

    DrawModel<PhongShader>(canvas2, model, mtl, vShader, Vec3{0, 1.5, 3});
    canvas2.save_ppm("test_result2.ppm");

    DrawModel<BlinnPhongShader>(canvas3, model, mtl, vShader, Vec3{0, 1.5, 3});
    canvas3.save_ppm("test_result3.ppm");

    DrawModel<CelShader>(canvas3, model, mtl, vShader, Vec3{0, 1.5, 3});
    canvas3.save_ppm("test_result4.ppm");

    DrawModel<UnlitShader>(canvas3, model, mtl, vShader, Vec3{0, 1.5, 3});
    canvas3.save_ppm("test_result5.ppm");
    return 0;
}