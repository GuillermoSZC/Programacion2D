#pragma once

#define PI 3.14159265359

class Vec2 {
public:
	Vec2();
	Vec2(float x, float y);
	union
	{
		float v[2];
		struct
		{
			float x, y;
		};
	};

	Vec2 operator+(const Vec2&);
	Vec2 operator-(const Vec2&);
	Vec2 operator*(const Vec2&);
	Vec2 operator/(const Vec2&);
	float AbsoluteVal(const Vec2&) const;
	Vec2 Normal(const Vec2&);
	float EscalarProduct(const Vec2&, const Vec2&);
	float Length() const;
	float Angle(const Vec2& other) const;
	float Distance(const Vec2& other) const;

};