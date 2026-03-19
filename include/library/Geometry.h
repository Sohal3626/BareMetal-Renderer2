//
// Created by Sohal03 on 26. 3. 19..
//

#ifndef TOYRENDERER2_GEOMETRY_H
#define TOYRENDERER2_GEOMETRY_H
#include <initializer_list>

template <int R, int C>
struct Mat {
    float data[R * C]{};
    int rows{R}, cols{C};

    // 생성자 짬통
    Mat() {
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (i == j) data[i * C + j] = 1.;
                else data[i * C + j] = 0.;
            }
        }
    }

    Mat(const Mat& m) {
        for (int i = 0; i < R * C; i++) {
            data[i] = m.data[i];
        }
    }

    float* operator[](int i) {
        return &data[i * C];
    }

    const float* operator[](int i) const {
        return &data[i * C];
    }
};

struct Vec3 {
    float x = 0, y = 0, z = 0;

    // 생성자 짬통
    Vec3() = default;
    Vec3(const Vec3& v3) = default;
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vec3(const std::initializer_list<float> list) {
        auto it = list.begin();
        while (it != list.end()) {
            if (it != list.end()) x = *it++;
            if (it != list.end()) y = *it++;
            if (it != list.end()) z = *it++;
        }
    }
    Vec3& operator=(const Vec3& v) = default;

    // 연산자 오버로딩

    // 벡터덧셈
    Vec3 operator+(Vec3& v) const { return {x + v.x, y + v.y, z + v.z}; }
    Vec3& operator+=(Vec3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    // 벡터뺼셈
    Vec3 operator-(Vec3& v) const { return {x - v.x, y - v.y, z - v.z}; }
    Vec3& operator-=(Vec3& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    // 스칼라곱셈
    Vec3 operator*(const float s) const { return {x * s, y * s, z * s}; }
    Vec3& operator*=(const float s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    // 스칼라나눗셈
    Vec3 operator/(const float s) const { return {x / s, y / s, z / s}; }
    Vec3& operator/=(const float s) {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }

    // 내적
    [[nodiscard]] float dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }

    // 외적
    Vec3 cross(const Vec3& v) const { return { y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x }; }

    //비교
    bool operator==(const Vec3& v) const = default;
};

struct Vec4 {
    float x = 0, y = 0, z = 0, w = 0;

    // 생성자 짬통
    Vec4() = default;
    Vec4(const Vec4& v4) = default;
    Vec4(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {}
    Vec4(const std::initializer_list<float> list) {
        auto it = list.begin();
        while (it != list.end()) {
            if (it != list.end()) x = *it++;
            if (it != list.end()) y = *it++;
            if (it != list.end()) z = *it++;
        }
    }
    Vec4& operator=(const Vec4& v) = default;

    // 연산자 오버로딩

    // 벡터덧셈
    Vec4 operator+(Vec4& v) const { return {x + v.x, y + v.y, z + v.z}; }
    Vec4& operator+=(const Vec3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    // 벡터뺼셈
    Vec4 operator-(Vec3& v) const { return {x - v.x, y - v.y, z - v.z}; }
    Vec4& operator-=(const Vec3& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    // 스칼라곱셈
    Vec4 operator*(const float s) const { return {x * s, y * s, z * s}; }
    Vec4& operator*=(const float s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    // 스칼라나눗셈
    Vec4 operator/(const float s) const { return {x / s, y / s, z / s}; }
    Vec4& operator/=(const float s) {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }

    // 내적
    [[nodiscard]] float dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }

    bool operator==(const Vec4 & vec4) const = default;

    /* 외적
    Vec4 cross(const Vec3& v) const
    {

    }
    */

};

struct Vec2 {
    float x, y;
    Vec2() : x(0), y(0) {}
    Vec2(float x, float y) : x(x), y(y) {}

    Vec2 operator+(const Vec2& v) const { return {x + v.x, y + v.y}; }
    Vec2 operator-(const Vec2& v) const { return {x - v.x, y - v.y}; }
    Vec2 operator*(float s) const { return {x * s, y * s}; }
    float& operator[](int i) { return (&x)[i]; }

    bool operator==(const Vec2 & vec2) const = default;
};

inline Vec4 operator*(const Mat<4, 4>& m, const Vec4& v) {
    float res[4] = {0, 0, 0, 0};
    for (int i = 0; i < 4; i++) {
        res[i] = m[i][0] * v.x + m[i][1] * v.y + m[i][2] * v.z + m[i][3] * v.w;
    }
    return {res[0], res[1], res[2], res[3]};
}

using Mat44 = Mat<4, 4>;

#endif //TOYRENDERER2_GEOMETRY_H