#pragma once
#include "Colliders.h"
#include <iostream>


class RectCollider : public Collider
{
public:
    RectCollider() { }
    virtual ~RectCollider() { printf("Rect collider deleted.\n"); }

public:
    bool CheckRectRect(const Vec2& _rectPos1, const Vec2& _rectSize1,
        const Vec2& _rectPos2, const Vec2& _rectSize2);

protected:
    bool Collides(const Collider& _other) const override
    {
        return false;
    }
    bool Collides(const Vec2& _circlePos, float _circleRadius) const override
    {
        return false;
    }
    bool Collides(const Vec2& _rectPos, Vec2& _rectSize) const override
    {
        return false;
    }
    //     bool Collides(const Vec2& _pixelsPos, Vec2& _pixelsSize,
    //         const uint8_t* _pixels) const override
    //     {
    //         return false;
    //     }

};