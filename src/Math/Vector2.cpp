#include "Math/Vector2.hpp"

Vector2 Vector2::operator+(const Vector2 &other) const
{
    return {x + other.x, y + other.y};
}

Vector2 Vector2::operator-(const Vector2 &other) const
{
    return {x - other.x, y - other.y};
}

Vector2 Vector2::operator*(float scalar) const
{
    return {x * scalar, y * scalar};
}

Vector2 Vector2::clamp(const Vector2 &min, const Vector2 &max) const
{
    return Vector2{
        std::clamp(x, min.x, max.x),
        std::clamp(y, min.y, max.y)
    };
}

float Vector2::length_squared() const
{
    return x * x + y * y;
}

float Vector2::length() const
{
    return std::sqrt(length_squared());
}

Vector2 Vector2::normalized() const
{
    float len = length();
    if (len > 0.0001f)
    {
        return {x / len, y / len};
    }
    return {0.0f, 0.0f};
}
