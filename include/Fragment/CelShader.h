//
// Created by desktop on 26. 7. 4..
//

#ifndef TOYRENDERER2_CELLSHADER_H
#define TOYRENDERER2_CELLSHADER_H

#include "../data/Material.h"
#include "FragmentIn.h"

class CelShader {
private:
    const material& mtl;
    Vec3 lightPos;
    Vec3 viewPos;
    const float globalAmbientIntensity = 0.0f;
    static inline Vec3 reflect(const Vec3& I, const Vec3& N) { return I - N * (2.0f * I.dot(N)); }
public:
    explicit CelShader(const material& m, const Vec3 lp, const Vec3 cp) : mtl(m), lightPos(lp), viewPos(cp) {}

    Vec3 operator()(const FragmentIn& in) const {
        const Vec3 N = normalize(Vec3{in.normal.x, in.normal.y, in.normal.z});
        const Vec3 L = normalize(lightPos - in.worldPos);
        const Vec3 V = normalize(viewPos - in.worldPos);

        const Vec3 I = L * -1.0f;
        const Vec3 R = reflect(I, N);

        if (mtl.materialId == 65535) {
            const float fakeDiff = std::max(N.dot(L), 0.2f);
            float intensity = 0.f;
            if (fakeDiff > 0.8f) intensity = 1.0f;
            else if (fakeDiff > 0.4f) intensity = 0.5f;
            else intensity = 0.15f;

            return Vec3{1.0f, 1.0f, 1.0f} * intensity;
        }

        const float diff = std::max(N.dot(L), 0.f);

        const auto& tex = mtl.texture;
        const auto& uv  = in.texCoord;
        Vec3 baseColor = (tex != nullptr) ? tex->get_color(uv.x, uv.y) : mtl.diffuse;
        if (baseColor.x == 0 && baseColor.y == 0 && baseColor.z == 0) {
            baseColor = Vec3{0.5f, 0.5f, 0.5f};
        }
        float intensity = 0.f;
        if (diff > 0.8f) intensity = 1.0f;
        else if (diff > 0.4f) intensity = 0.75f;
        else intensity = 0.5f;
        const float spec = std::pow(std::max(V.dot(R), 0.0f), mtl.shininess);
        baseColor = baseColor * intensity;
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

#endif //TOYRENDERER2_CELLSHADER_H