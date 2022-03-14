#pragma once
#include "Vec2.h"
#include <iostream>
#include <cstdint>

class Collider
{
public:
    Vec2 circlePosition;
    Vec2 rectPosition;
    Vec2 pixelPosition;
    int collisionType;
    float radius;
    Vec2 rectSize;
    Vec2 pixelSize;
    uint8_t* pixels;

    virtual bool CheckCircleCircle(const Vec2& _pos1, float _radius1, const Vec2& _pos2, float _radius2) const;
    virtual bool CheckCircleRect(const Vec2& _circlePos, float _circleRadius, const Vec2& _rectPos, const Vec2& _rectSize) const;
    virtual bool CheckRectRect(const Vec2& _rectPos1, const Vec2& _rectSize1, const Vec2& _rectPos2, const Vec2& _rectSize2) const;
    virtual bool CheckCirclePixels(const Vec2& _circlePos1, float _circleRadius, const Vec2& _pixelsPos, const Vec2& _pixelsSize, const uint8_t* _pixels) const;
    virtual bool CheckPixelsRect(const Vec2& _pixelsPos, const Vec2& _pixelsSize, const uint8_t* _pixels, const Vec2& _rectPos, const Vec2& _rectSize) const;
    virtual bool CheckPixelsPixels(const Vec2& _pixelsPos1, const Vec2& _pixelsSize1, const uint8_t* _pixels1, const Vec2& _pixelsPos2, const Vec2& _pixelsSize2, const uint8_t* _pixels2) const;

    virtual bool Collides(const Collider& _other) const = 0;
    virtual bool Collides(const Vec2& _circlePos, float _circleRadius) const = 0;
    virtual bool Collides(const Vec2& _rectPos, const Vec2& _rectSize) const = 0;
    virtual bool Collides(const Vec2& _pixelsPos, const Vec2& _pixelsSize,
        const uint8_t* _pixels) const = 0;
};

class PixelsCollider : public Collider
{
public:
    PixelsCollider() { }
    ~PixelsCollider() { printf("Pixel collider deleted.\n"); }

    bool Collides(const Collider& _other) const override;
    bool Collides(const Vec2& _circlePos, float _circleRadius) const override;
    bool Collides(const Vec2& _rectPos, const Vec2& _rectSize) const override;
    bool Collides(const Vec2& _pixelsPos, const Vec2& _pixelsSize,
        const uint8_t* _pixels) const override;

};

class CircleCollider : public Collider
{
public:
    CircleCollider() { }
    virtual ~CircleCollider() { printf("Circle collider deleted.\n"); }

    virtual bool Collides(const Collider& _other) const override;
    virtual bool Collides(const Vec2& _circlePos, float _circleRadius) const override;
    virtual bool Collides(const Vec2& _rectPos, const Vec2& _rectSize) const override;
    virtual bool Collides(const Vec2& _pixelsPos, const Vec2& _pixelsSize,
        const uint8_t* _pixels) const override;

};

class RectCollider : public Collider
{
public:
    RectCollider() { }
    virtual ~RectCollider() { printf("Rect collider deleted.\n"); }

    bool Collides(const Collider& _other) const override;
    bool Collides(const Vec2& _circlePos, float _circleRadius) const override;
    bool Collides(const Vec2& _rectPos, const Vec2& _rectSize) const override;
    bool Collides(const Vec2& _pixelsPos, const Vec2& _pixelsSize,
        const uint8_t* _pixels) const override;
};