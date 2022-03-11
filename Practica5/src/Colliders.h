#pragma once
#include "Vec2.h"
#include <cstdint>

class Collider
{
protected:
    virtual bool Collides(const Collider& _other) const = 0;
    virtual bool Collides(const Vec2& _circlePos, float _circleRadius) const = 0;
    virtual bool Collides(const Vec2& _rectPos, Vec2& _rectSize) const = 0;
//     virtual bool Collides(const Vec2& pixelsPos, const Vec2& pixelsSize,
//         const uint8_t* pixels) const = 0;

};