#include "vec2.h"
#include <math.h>

vec2::vec2() {}

vec2::vec2(float x, float y)
{
	v[0] = x;
	v[1] = y;
}

vec2 vec2::operator+(const vec2& a)
{
	vec2 sum;
	sum.x = x + a.x;
	sum.y = y + a.y;

	return sum;
}
vec2 vec2::operator-(const vec2& a)
{
	vec2 rest;

	rest.x = x - a.x;
	rest.y = y - a.y;

	return rest;
}

vec2 vec2::operator*(const vec2& a)
{
	vec2 prod;
	prod.x = x * a.x;
	prod.y = y * a.y;

	return prod;
}

vec2 vec2::operator/(const vec2& a)
{
	vec2 div;
	div.x = x / a.x;
	div.y = y / a.y;

	return div;
}

float vec2::vAbsoluto(const vec2 &_vector) const
{
	return sqrtf(_vector.v[0] * _vector.v[0] + _vector.v[1] * _vector.v[1]);
}

vec2 vec2::normal(const vec2& _vector)
{
	vec2 vector_;
	float nm = vAbsoluto(_vector);
	if (nm == 0.f)
	{
		return vec2(0.f, 0.f);
	}
	vector_.v[0] = _vector.v[0] / nm;
	vector_.v[1] = _vector.v[1] / nm;

	return vector_;
}

float vec2::pEscalar(const vec2& a, const vec2& b)
{
	float escalar = a.x * b.y + a.x * b.y;

	return escalar;
}

float vec2::angle(const vec2& other) const 
{
	double fAng = atan2f(y - other.y, x - other.x) * (180 / PI);
	if (fAng < 0) { fAng += 360.f; }
	
	return (float)fAng;
}

float vec2::distance(const vec2& other) const
{
	vec2 vector(x, y);
	vector = vector - other;
	float fDistance = vAbsoluto(vector);

	return fDistance;
}