#include "CircleCollider.h"
#include <iostream>

bool CircleCollider::CheckCircleCircle(const Vec2& _pos1, float _radius1, const Vec2& _pos2, float _radius2)
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

bool CircleCollider::CheckCircleRect(const Vec2& _circlePos, float _circleRadius, const Vec2& _rectPos, const Vec2& _rectSize)
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
