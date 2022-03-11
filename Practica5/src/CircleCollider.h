#pragma once
#include "Vec2.h"
#include "Colliders.h"
#include <iostream>

class CircleCollider : public Collider
{
public:
    CircleCollider() { }
    virtual ~CircleCollider() { printf("Circle collider deleted.\n"); }

public:
    bool CheckCircleCircle(const Vec2& _pos1, float _radius1,
        const Vec2& _pos2, float _radius2);
    bool CheckCircleRect(const Vec2& _circlePos, float _circleRadius,
        const Vec2& _rectPos, const Vec2& _rectSize);


protected:
    virtual bool Collides(const Collider& _other) const override
    {
        return false;
    }
    virtual bool Collides(const Vec2& _circlePos, float _circleRadius) const override
    {
        return false;
    }
    virtual bool Collides(const Vec2& _rectPos, Vec2& _rectSize) const override
    {
        return false;
    }
//     virtual bool Collides(const Vec2& _pixelsPos, Vec2& _pixelsSize,
//         const uint8_t* _pixels) const override
//     {
//         return false;
//     }

};