#pragma once

#include <cmath>
#include <algorithm>

struct Vector2
{
    float x{0.0f};
    float y{0.0f};

    // Constructores constexpr (deben permanecer en el .hpp)
    constexpr Vector2() = default;
    constexpr Vector2(float x, float y) : x(x), y(y) {}

    // Operadores
    Vector2 operator+(const Vector2 &other) const;
    Vector2 operator-(const Vector2 &other) const;
    Vector2 operator*(float scalar) const;

    // Métodos de utilidad y magnitud
    Vector2 clamp(const Vector2 &min, const Vector2 &max) const;
    float length_squared() const;
    float length() const;
    Vector2 normalized() const;
};
