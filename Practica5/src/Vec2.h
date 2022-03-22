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
	float vAbsoluto(const Vec2&) const;
	Vec2 normal(const Vec2&);
	float pEscalar(const Vec2&, const Vec2&);
	float Length() const;
	float angle(const Vec2& other) const;
	float distance(const Vec2& other) const;

};