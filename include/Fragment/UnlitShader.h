//
// Created by desktop on 26. 7. 4..
//

#ifndef TOYRENDERER2_UNLITSHADER_H
#define TOYRENDERER2_UNLITSHADER_H

#include "../data/Material.h"
#include "FragmentIn.h"

class UnlitShader {
public:
    const material& mtl;

    explicit UnlitShader(const material& m, const Vec3 lp, const Vec3 cp) : mtl(m) {}

    Vec3 operator()(const FragmentIn& in) const {
        if (mtl.materialId == 65535) {
            return Vec3{1.0f, 1.0f, 1.0f};
        }

        const auto& tex = mtl.texture;
        const auto& uv  = in.texCoord;

        Vec3 baseColor = (tex != nullptr) ? tex->get_color(uv.x, uv.y) : mtl.diffuse;

        if (baseColor.x == 0.0f && baseColor.y == 0.0f && baseColor.z == 0.0f) {
            baseColor = Vec3{0.5f, 0.5f, 0.5f};
        }

        constexpr float gamma = 1.4f;
        const Vec3 finalColor{
            std::pow(std::max(baseColor.x, 0.0f), 1.0f / gamma),
            std::pow(std::max(baseColor.y, 0.0f), 1.0f / gamma),
            std::pow(std::max(baseColor.z, 0.0f), 1.0f / gamma)
        };
        return Vec3{
            std::min(finalColor.x, 1.0f),
            std::min(finalColor.y, 1.0f),
            std::min(finalColor.z, 1.0f)
        };
    }
};

#endif //TOYRENDERER2_UNLITSHADER_H