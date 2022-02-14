#pragma once

#define PI 3.14159265359

class vec2 {
public:
	vec2();
	vec2(float x, float y);
	union
	{
		float v[2];
		struct
		{
			float x, y;
		};
	};

	vec2 operator+(const vec2&);
	vec2 operator-(const vec2&);
	vec2 operator*(const vec2&);
	vec2 operator/(const vec2&);
	float vAbsoluto(const vec2&) const;
	vec2 normal(const vec2&);
	float pEscalar(const vec2&, const vec2&);

	float angle(const vec2& other) const;
	float distance(const vec2& other) const;

};