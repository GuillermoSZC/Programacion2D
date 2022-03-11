#include "RectCollider.h"

bool RectCollider::CheckRectRect(const Vec2& _rectPos1, const Vec2& _rectSize1, const Vec2& _rectPos2, const Vec2& _rectSize2)
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
