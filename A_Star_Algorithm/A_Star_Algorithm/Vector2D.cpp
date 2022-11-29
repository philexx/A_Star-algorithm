#include "Vector2D.h"

vec2::vec2(float X, float Y)
{
    x = X;
    y = Y;
}

vec2 vec2::operator+(const vec2& rhs) const
{
    return vec2(x + rhs.x, y + rhs.y);
}

vec2& vec2::operator+=(const vec2& rhs)
{
    return *this = *this + rhs;
}

vec2 vec2::operator-(const vec2& rhs) const
{
    return vec2(x - rhs.x, y - rhs.y);
}

vec2& vec2::operator-=(const vec2& rhs)
{
    return *this = *this - rhs;
}

vec2 vec2::operator*(const vec2& rhs) const
{
    return vec2(x * rhs.x, y * rhs.y);
}

vec2& vec2::operator*=(const vec2& rhs)
{
    return *this = *this * rhs;
}

vec2 vec2::operator*(const float rhs) const
{
    return vec2(x * rhs, y * rhs);
}

vec2& vec2::operator*=(const float rhs)
{
    return *this = *this * rhs;
}

float vec2::Magnitude() const
{
    return static_cast<float>(sqrt(x * x + y * y));
}

void vec2::Normalize()
{
   const float Mag = this->Magnitude();
    x = x / Mag;
    y = y / Mag;
}
