#include "Vec2.h"
#include <cmath>

Vec2::Vec2() = default;

Vec2::Vec2(float x, float y)
{
	v[0] = x;
	v[1] = y;
}

Vec2 Vec2::operator+(const Vec2& a)
{
	Vec2 sum;
	sum.x = x + a.x;
	sum.y = y + a.y;

	return sum;
}
Vec2 Vec2::operator-(const Vec2& a)
{
	Vec2 rest;

	rest.x = x - a.x;
	rest.y = y - a.y;

	return rest;
}

Vec2 Vec2::operator*(const Vec2& a)
{
	Vec2 prod;
	prod.x = x * a.x;
	prod.y = y * a.y;

	return prod;
}

Vec2 Vec2::operator/(const Vec2& a)
{
	Vec2 div;
	div.x = x / a.x;
	div.y = y / a.y;

	return div;
}

float Vec2::Length() const
{
	return sqrtf(x * x + y * y);
}

float Vec2::AbsoluteVal(const Vec2 &_vector) const
{
	return sqrtf(_vector.v[0] * _vector.v[0] + _vector.v[1] * _vector.v[1]);
}


Vec2 Vec2::Normal(const Vec2& _vector)
{
	Vec2 vector_;
	float nm = AbsoluteVal(_vector);
	if (nm == 0.f)
	{
		return {0.f, 0.f};
	}
	vector_.v[0] = _vector.v[0] / nm;
	vector_.v[1] = _vector.v[1] / nm;

	return vector_;
}

float Vec2::EscalarProduct(const Vec2& a, const Vec2& b)
{
	return a.x * b.y + a.x * b.y;
}

float Vec2::Angle(const Vec2& other) const 
{
	double fAng = atan2f(y - other.y, x - other.x) * (180 / PI);
	if (fAng < 0) { fAng += 360.f; }
	
	return (float)fAng;
}

float Vec2::Distance(const Vec2& other) const
{
	Vec2 vector(x, y);
	vector = vector - other;
	float fDistance = AbsoluteVal(vector);

	return fDistance;
}