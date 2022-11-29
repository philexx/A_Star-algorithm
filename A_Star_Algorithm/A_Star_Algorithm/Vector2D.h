#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>

class vec2
{
public:
	float x;
	float y;

	vec2() = default;
	vec2(float X, float Y);
	vec2 operator + (const vec2& rhs) const;
	vec2& operator += (const vec2& rhs);
	vec2 operator - (const vec2& rhs) const;
	vec2& operator -= (const vec2& rhs);
	vec2 operator * (const vec2& rhs) const;
	vec2& operator *= (const vec2& rhs);
	vec2 operator * (const float rhs) const;
	vec2& operator *= (const float rhs);

	float Magnitude() const;

	void Normalize();


};
#endif // !VECTOR2D_H
