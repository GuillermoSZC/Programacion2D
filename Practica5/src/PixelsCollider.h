#pragma once
#include "Colliders.h"

class PixelsCollider : public Collider
{
public:
    PixelsCollider();
    ~PixelsCollider();

public:
    bool CheckCirclePixels(const Vec2& _circlePos1, float _circleRadius,
        const Vec2& _pixelsPos, const Vec2& _pixelsSize, const uint8_t* _pixels);
    bool CheckPixelsRect(const Vec2& _pixelsPos, const Vec2& _pixelsSize, const uint8_t* _pixels,
        const Vec2& _rectPos, Vec2& _rectSize);

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