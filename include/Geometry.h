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
                if (i == j) data[i * C + j] = 1.0f;
                else data[i * C + j] = 0.0f;
            }
        }
    }

    Mat(const Mat& m) {
        for (int i = 0; i < R * C; i++) {
            data[i] = m.data[i];
        }
    }

    float* operator[](int i) {
        return &data[i * C]; // i번째 행의 시작 주소 반환
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
    Vec3 operator+(Vec3&& v) const {
        return {x + v.x, y + v.y, z + v.z};
    }

    Vec3& operator+=(Vec3&& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    // 벡터뺼셈
    Vec3 operator-(Vec3&& v) const {
        return {x - v.x, y - v.y, z - v.z};
    }

    Vec3& operator-=(Vec3&& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    // 스칼라곱셈
    Vec3 operator*(const float s) const {
        return {x * s, y * s, z * s};
    }

    Vec3& operator*=(const float s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    // 스칼라나눗셈
    Vec3 operator/(const float s) const {
        return {x / s, y / s, z / s};
    }

    Vec3& operator/=(const float s) {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }

    // 내적
    [[nodiscard]] Vec3 dot(const Vec3& v) const {
        return {x * v.x, y * v.y, z * v.z};
    }

    /* 외적
    Vec3 cross(const Vec3& v) const
    {

    }
    */



};

#endif //TOYRENDERER2_GEOMETRY_H