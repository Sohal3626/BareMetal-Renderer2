#include <iostream>

#include "include/data/Mesh.h"

// TIP 코드를 <b>Run</b>하려면 <shortcut actionId="Run"/>을(를) 누르거나 여백에서 <icon src="AllIcons.Actions.Execute"/> 아이콘을 클릭하세요.
int main()
{
    Mesh mesh;
    mesh.load_obj("../obj/Miyu.obj");
}