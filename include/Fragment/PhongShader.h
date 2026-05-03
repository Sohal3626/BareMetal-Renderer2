//
// Created by desktop on 26. 5. 2..
//

#ifndef TOYRENDERER2_PHONGSHADER_H
#define TOYRENDERER2_PHONGSHADER_H

#include "../data/Material.h"
#include "FragmentIn.h"

class PhongShader{
public:
    const material& mtl;
    Vec3 lightPos;

    explicit PhongShader(const material& m, const Vec3 lp) : mtl(m), lightPos(lp) {}

    Vec3 operator()(const FragmentIn& in) const {
        const Vec3 N = normalize(Vec3{in.normal.x, in.normal.y, in.normal.z});
        const Vec3 L = normalize(lightPos - Vec3{in.worldPos.x, in.worldPos.y, in.worldPos.z});

        if (mtl.materialId == 65535) {
            const float fakeDiff = std::max(N.dot(L), 0.2f);
            return Vec3{1.0f, 1.0, 1.0f} * fakeDiff;
        }

        const float diff = std::max(N.dot(L), 0.f);

        Vec3 baseColor = mtl.diffuse;
        if (baseColor.x == 0 && baseColor.y == 0 && baseColor.z == 0) {
            baseColor = Vec3{0.5f, 0.5f, 0.5f};
        }

        return baseColor * diff + mtl.ambient * globalAmbientIntensity;
    }
private:
    const float globalAmbientIntensity = 0.5f;
};

#endif //TOYRENDERER2_PHONGSHADER_H