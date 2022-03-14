#include "Colliders.h"
#pragma region CHECK_COLLIDERS
bool Collider::CheckCircleCircle(const Vec2& _pos1, float _radius1, const Vec2& _pos2, float _radius2) const
{
    float distX = _pos1.x - _pos2.x;
    float distY = _pos1.y - _pos2.y;
    float distance = sqrt((distX * distX) + (distY * distY));
    if (distance <= _radius1 + _radius2)
    {     
        return true;
    }
    return false;
}

bool Collider::CheckCircleRect(const Vec2& _circlePos, float _circleRadius, const Vec2& _rectPos, const Vec2& _rectSize) const
{
    float edgeX = _circlePos.x;
    float edgeY = _circlePos.y;

    if (_circlePos.x < _rectPos.x)
    {
        edgeX = _rectPos.x;
    }
    else if (_circlePos.x > _rectPos.x + _rectSize.x)
    {
        edgeX = _rectPos.x + _rectSize.x;
    }
    if (_circlePos.y < _rectPos.y)
    {
        edgeY = _rectPos.y;
    }
    else if (_circlePos.y > _rectPos.y + _rectSize.y)
    {
        edgeY = _rectPos.y + _rectSize.y;
    }

    float distX = _circlePos.x - edgeX;
    float distY = _circlePos.y - edgeY;
    float distance = sqrt((distX * distX) + (distY * distY));

    if (distance <= _circleRadius)
    {
        return true;
    }
    return false;
}

bool Collider::CheckRectRect(const Vec2& _rectPos1, const Vec2& _rectSize1, const Vec2& _rectPos2, const Vec2& _rectSize2) const
{
    if (_rectPos1.x + _rectSize1.x >= _rectPos2.x && // rect1 right edge past rect2 left
        _rectPos1.x <= _rectPos2.x + _rectSize2.x && // rect1 left edge past rect2 right
        _rectPos1.y + _rectSize1.y >= _rectPos2.y && // rect1 top edge past rect2 bottom
        _rectPos1.y <= _rectPos2.y + _rectSize2.y)   // rect1 bottom edge past rect2 top
    {
        return true;
    }
    return false;
}

bool Collider::CheckCirclePixels(const Vec2& _circlePos1, float _circleRadius, const Vec2& _pixelsPos, const Vec2& _pixelsSize, const uint8_t* _pixels) const
{
    
    return false;
}

bool Collider::CheckPixelsRect(const Vec2& _pixelsPos, const Vec2& _pixelsSize, const uint8_t* _pixels, const Vec2& _rectPos, const Vec2& _rectSize) const
{
    if (_rectPos.x + _rectSize.x >= _pixelsPos.x &&
        _rectPos.x <= _pixelsPos.x + _pixelsSize.x && 
        _rectPos.y + _rectSize.y >= _pixelsPos.y &&
        _rectPos.y <= _pixelsPos.y + _pixelsSize.y)   
    {
        return true;
    }
    return false;
}

bool Collider::CheckPixelsPixels(const Vec2& _pixelsPos1, const Vec2& _pixelsSize1, const uint8_t* _pixels1, const Vec2& _pixelsPos2, const Vec2& _pixelsSize2, const uint8_t* _pixels2) const
{
    return false;
}

#pragma endregion

#pragma region CIRCLE_COLLIDER

bool CircleCollider::Collides(const Collider& _other) const
{
    return _other.Collides(circlePosition, radius);
}

bool CircleCollider::Collides(const Vec2& _circlePos, float _circleRadius) const
{
    return CheckCircleCircle(circlePosition, radius, _circlePos, _circleRadius);
}

bool CircleCollider::Collides(const Vec2& _rectPos, const Vec2& _rectSize) const
{
    return CheckCircleRect(circlePosition, radius, _rectPos, _rectSize);
}

bool CircleCollider::Collides(const Vec2& _pixelsPos, const Vec2& _pixelsSize, const uint8_t* _pixels) const
{
    return CheckCirclePixels(circlePosition, radius, _pixelsPos, _pixelsSize, _pixels);
}
#pragma endregion
#pragma region RECT_COLLIDER
bool RectCollider::Collides(const Collider& _other) const
{
    return _other.Collides(rectPosition, rectSize);
}

bool RectCollider::Collides(const Vec2& _circlePos, float _circleRadius) const
{
    return CheckCircleRect(_circlePos, _circleRadius, rectPosition, rectSize);
}

bool RectCollider::Collides(const Vec2& _rectPos, const Vec2& _rectSize) const
{
    return CheckRectRect(rectPosition, rectSize, _rectPos, _rectSize);
}

bool RectCollider::Collides(const Vec2& _pixelsPos, const Vec2& _pixelsSize, const uint8_t* _pixels) const
{
    return CheckPixelsRect(_pixelsPos, _pixelsSize, _pixels, rectPosition, rectSize);
}
#pragma endregion
#pragma region PIXEL_COLLIDER

bool PixelsCollider::Collides(const Collider& _other) const
{
    return _other.Collides(pixelPosition, pixelSize, pixels);
}

bool PixelsCollider::Collides(const Vec2& _circlePos, float _circleRadius) const
{
    return CheckCirclePixels(_circlePos, _circleRadius, pixelPosition, pixelSize, pixels);
}

bool PixelsCollider::Collides(const Vec2& _rectPos, const Vec2& _rectSize) const
{
    return CheckPixelsRect(pixelPosition, pixelSize, pixels, _rectPos, _rectSize);
}

bool PixelsCollider::Collides(const Vec2& _pixelsPos, const Vec2& _pixelsSize, const uint8_t* _pixels) const
{
    return CheckPixelsPixels(pixelPosition, pixelSize, pixels, _pixelsPos, _pixelsSize, _pixels);
}
#pragma endregion
