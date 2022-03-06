#pragma once
#include "Vec2.h"

class Collider
{

public: // Constructor & Destructor
    Collider();
    ~Collider();

protected:
    virtual bool Collides(const Collider& _other) const = 0;
    virtual bool Collides(const Vec2& _circlePos, float _circleRadius) const = 0;
    virtual bool Collides(const Vec2& _rectPos, Vec2& _rectSize) const = 0;
    virtual bool Collides(const Vec2& _pixelsPos, Vec2& _pixelsSize,
        const uint8_t* _pixels) const = 0;

};

class CircleCollider : public Collider
{
public:
    CircleCollider();
    ~CircleCollider();

public:
    bool CheckCircleCircle(const Vec2& _pos1, float _radius1,
        const Vec2& _pos2, float _radius2);
    bool CheckCircleRect(const Vec2& _circlePos, float _circleRadius,
        const Vec2& _rectPos, const Vec2& _rectSize);


protected:
    bool Collides(const Collider& _other) const override;
    bool Collides(const Vec2& _circlePos, float _circleRadius) const override;
    bool Collides(const Vec2& _rectPos, Vec2& _rectSize) const override;
    bool Collides(const Vec2& _pixelsPos, Vec2& _pixelsSize, 
        const uint8_t* _pixels) const override;

};

class RectCollider : public Collider
{
public:
    RectCollider();
    ~RectCollider();

public:
    bool _checkRectRect(const Vec2& _rectPos1, const Vec2& _rectSize1,
        const Vec2& _rectPos2, const Vec2& _rectSize2);

protected:
    bool Collides(const Collider& _other) const override;
    bool Collides(const Vec2& _circlePos, float _circleRadius) const override;
    bool Collides(const Vec2& _rectPos, Vec2& _rectSize) const override;
    bool Collides(const Vec2& _pixelsPos, Vec2& _pixelsSize, 
        const uint8_t* _pixels) const override;

};

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
    bool CheckPixelsPixels(const Vec2& _pixelsPos1, const Vec2& _pixelsSize1, const uint8_t* _pixels1, 
        const Vec2& _pixelsPos2, const Vec2& _pixelsSize2, const uint8_t* _pixels2);

protected:
    bool Collides(const Collider& _other) const override;
    bool Collides(const Vec2& _circlePos, float _circleRadius) const override;
    bool Collides(const Vec2& _rectPos, Vec2& _rectSize) const override;
    bool Collides(const Vec2& _pixelsPos, Vec2& _pixelsSize, 
        const uint8_t* _pixels) const override;

};