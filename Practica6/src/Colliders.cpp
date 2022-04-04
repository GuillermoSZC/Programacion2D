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

bool Collider::CheckCirclePixels(const Vec2& _circlePos, float _circleRadius, const Vec2& _pixelsPos, const Vec2& _pixelsSize, const uint8_t* _pixels) const
{
    float xPosition = 0.f, yPosition = 0.f;
    float width = 0.f, height = 0.f;
    int pixelPosX = 0;
    int pixelPosY = 0;
    int index = 0;
    Vec2 distance = Vec2(0.f, 0.f);
    Vec2 circleSize = Vec2(_circlePos.x - _circleRadius, _circlePos.y - _circleRadius);

    if (_pixelsPos.x < circleSize.x)
    {
        xPosition = circleSize.x;
    }
    else
    {
        xPosition = _pixelsPos.x;
    }
    width = std::fminf(_pixelsPos.x + _pixelsSize.x, circleSize.x + (_circleRadius * 2)) - xPosition;
    if (_pixelsPos.y < circleSize.y)
    {
        yPosition = circleSize.y;
    }
    else
    {
        yPosition = _pixelsPos.y;
    }
    height = std::fminf(_pixelsPos.y + _pixelsSize.y, circleSize.y + (_circleRadius * 2)) - yPosition;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            distance = Vec2(j + xPosition, i + yPosition) - _circlePos;
            if (distance.Length() < _circleRadius)
            {
                pixelPosX = j + xPosition - _pixelsPos.x;
                pixelPosY = i + yPosition - _pixelsPos.y;
                index = (pixelPosY * _pixelsSize.x + pixelPosX) * 4 + 3;
                if (_pixels[index] != 0)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Collider::CheckPixelsRect(const Vec2& _pixelsPos, const Vec2& _pixelsSize, const uint8_t* _pixels, const Vec2& _rectPos, const Vec2& _rectSize) const
{
    float xPosition = 0.f, yPosition = 0.f;
    float width = 0.f, height = 0.f;
    int pixelPosX = 0;
    int pixelPosY = 0;
    int index = 0;

    if (_pixelsPos.x < _rectPos.x)
    {
        xPosition = _rectPos.x;
    }
    else
    {
        xPosition = _pixelsPos.x;
    }
    width = std::fminf(_pixelsPos.x + _pixelsSize.x, _rectPos.x + _rectSize.x) - xPosition;
    if (_pixelsPos.y < _rectPos.y)
    {
        yPosition = _rectPos.y;
    }
    else
    {
        yPosition = _pixelsPos.y;
    }
    height = std::fminf(_pixelsPos.y + _pixelsSize.y, _rectPos.y + _rectSize.y) - yPosition;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            pixelPosX = j + xPosition - _pixelsPos.x;
            pixelPosY = i + yPosition - _pixelsPos.y;
            index = (pixelPosY * _pixelsSize.x + pixelPosX) * 4 + 3;
            if (_pixels[index] != 0)
            {
                return true;
            }
        }
    }
    return false;
}

bool Collider::CheckPixelsPixels(const Vec2& _pixelsPos1, const Vec2& _pixelsSize1, const uint8_t* _pixels1, const Vec2& _pixelsPos2, const Vec2& _pixelsSize2, const uint8_t* _pixels2) const
{
    float xPosition = 0.f, yPosition = 0.f;
    float width = 0.f, height = 0.f;
    int pixelPosX1 = 0, pixelPosX2 = 0;
    int pixelPosY1 = 0, pixelPosY2 = 0;
    int index1 = 0, index2 = 0;

    if (_pixelsPos1.x < _pixelsPos2.x)
    {
        xPosition = _pixelsPos2.x;
    }
    else
    {
        xPosition = _pixelsPos1.x;
    }
    width = std::fminf(_pixelsPos1.x + _pixelsSize1.x, _pixelsPos2.x + _pixelsSize2.x) - xPosition;
    if (_pixelsPos1.y < _pixelsPos2.y)
    {
        yPosition = _pixelsPos2.y;
    }
    else
    {
        yPosition = _pixelsPos1.y;
    }
    height = std::fminf(_pixelsPos1.y + _pixelsSize1.y, _pixelsPos2.y + _pixelsSize2.y) - yPosition;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            pixelPosX1 = j + xPosition - _pixelsPos1.x;
            pixelPosY1 = i + yPosition - _pixelsPos1.y;
            index1 = (pixelPosY1 * _pixelsSize1.x + pixelPosX1) * 4 + 3;
            pixelPosX2 = j + xPosition - _pixelsPos2.x;
            pixelPosY2 = i + yPosition - _pixelsPos2.y;
            index2 = (pixelPosY2 * _pixelsSize2.x + pixelPosX2) * 4 + 3;
            if (_pixels1[index1] != 0 && _pixels2[index2])
            {
                return true;
            }
        }
    }

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
