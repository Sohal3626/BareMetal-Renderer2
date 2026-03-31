#include <iostream>

#include "include/Canvas.h"
#include "include/Rasterizer.h"
#include "include/VertexShader.h"
#include "include/data/Mesh.h"

// TIP 코드를 <b>Run</b>하려면 <shortcut actionId="Run"/>을(를) 누르거나 여백에서 <icon src="AllIcons.Actions.Execute"/> 아이콘을 클릭하세요.
int main() {
    constexpr int width = 800;
    constexpr int height = 600;
    Canvas canvas(width, height);

    TFVertex triangle[] = {
        TFVertex{ Vec4(400, 100, 0, 1), Vec2{1.f, 0.f} },
        TFVertex{ Vec4(100, 500, 0, 1), Vec2(0.f, 1.f) },
        TFVertex{ Vec4(700, 500, 0, 1), Vec2(0.f, 0.f) }
    };

    FillTriangle(canvas, triangle);

    canvas.save_ppm("triangle_test.ppm");

    return 0;
}