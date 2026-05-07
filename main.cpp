    #include <iostream>
    #include <ranges>

    #include "include/Canvas.h"
    #include "include/Renderer.h"
    #include "include/VertexShader.h"
    #include "include/data/Mesh.h"
    #include "include/library/Geometry.h"
    #include "include/Fragment/PhongShader.h"
    #include "include/Fragment/BlinnPhongShader.h"

    // TIP 코드를 <b>Run</b>하려면 <shortcut actionId="Run"/>을(를) 누르거나 여백에서 <icon src="AllIcons.Actions.Execute"/> 아이콘을 클릭하세요.
    int main() {
        constexpr int width = 1920;
        constexpr int height = 1080;
        Canvas canvas(width, height);
        Canvas canvas2(width, height);

        Mesh model;
        model.loadObj("../obj/Mymodel.obj");

        Material mtl;
        mtl.loadMtl("../mtl/Mytml.mtl");

        // 3. 행렬 준비
        Mat44 modelMat;
        translate(modelMat, 0, -0.7, -2.0);
        rotate (modelMat, 0, 0, 0);

        Mat44 viewMat;

        translate(viewMat, 0, 0, -1.f);
        const Mat44 projectionMat =
            perspective(45.0f, static_cast<float>(width)/static_cast<float>(height), 0.1f, 1000.0f);

        // 4. 버텍스 셰이더 생성
        const VertexShader vShader(modelMat, viewMat, projectionMat);

        // 5. 렌더링 시작
        DrawModel<PhongShader>(canvas, model, mtl, vShader, Vec3{0, 0, 3});

        // 6. 결과 확인
        canvas.save_ppm("test_result.ppm");

        DrawModel<BlinnPhongShader>(canvas2, model, mtl, vShader, Vec3{0, 0, 3});
        canvas2.save_ppm("test_result2.ppm");
        return 0;
    }