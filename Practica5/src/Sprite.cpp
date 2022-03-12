#include <iostream>
#include "litegfx.h"
#include "Vec2.h"
#include "Sprite.h"

#pragma region Sprite

void Sprite::SetTexture(ltex_t* _tex)
{
    tex = _tex;
}

void Sprite::DrawTexture(float _xPosition, float _yPosition)
{
    ltex_drawrotsized(tex, _xPosition - tex->width * 0.5f, _yPosition - tex->height * 0.5f, 0, 0, 0, tex->width, tex->height, 0, 0, 1, 1);
}

void Sprite::SetAnimTexture(const ltex_t* _Tex/*, int _HFrames, int _VFrames*/)
{
    ltex_drawrotsized(_Tex, position.x, position.y, angle, 0, 0,
        _Tex->width / 8.f * 2.f, _Tex->height * 2.f, 0.125f * GetCurrentFrame(), 0.f, 0.125f * GetCurrentFrame() + 0.125f, 1.f);
}

void Sprite::SetColor(float _R, float _G, float _B, float _A)
{
    r = _R;
    g = _G;
    b = _B;
    a = _A;
}


void Sprite::Update(float _DeltaTime)
{
    FPS += _DeltaTime * 8;

    if (FPS > 1)
    {
        SetCurrentFrame(1);
        FPS = 0;
    }
}

void Sprite::SetSize(float _width, float _height)
{
    size.x = _width;
    size.y = _height;
}

Vec2 Sprite::GetSize() const
{
    return size;
}

float Sprite::GetCurrentFrame() const
{
    return frame;
}

void Sprite::SetCurrentFrame(float _Frame)
{
    frame += _Frame;

    if (frame > 6)
    {
        frame = 0;
    }
}

void Sprite::SetPosition(const Vec2& _Position)
{
    position = _Position;
}

void Sprite::SetAnimPosition(const Vec2& _Position)
{
    position.x += (_Position.x - 50 - position.x) / 128;
    position.y += (_Position.y - 50 - position.y) / 128;
}

void Sprite::SetAngle(float _Angle)
{
    angle += _Angle;
}
#pragma endregion

#pragma region Collider

void Sprite::SetCollisionType(CollisionType _type)
{
    switch (_type)
    {
    case COLLISION_NONE:
        break;
    case COLLISION_CIRCLE:
        if (collider != nullptr)
        {
            delete& collider;
        }
        collider = new CircleCollider();
        collider->collisionType = 1;
        collider->circlePosition = position;
        collider->radius = tex->width * 0.5f;

        break;
    case COLLISION_RECT:
        if (collider != nullptr)
        {
            delete& collider;
        }
        collider = new RectCollider();
        collider->collisionType = 2;
        collider->rectPosition = position;
        collider->rectSize = Vec2(tex->width, tex->height);

        break;
    case COLLISION_PIXELS:
        if (collider != nullptr)
        {
            delete& collider;
        }
        collider = new PixelsCollider();
        collider->collisionType = 3;
        collider->pixelPosition = position;
        collider->pixelSize = Vec2(tex->width, tex->height);

        int iSize = tex->width * tex->height * 4;
        unsigned char* buffer = new unsigned char[iSize];
        ltex_getpixels(tex, buffer);
        collider->pixels = buffer;

        break;
    }
}

bool Sprite::Collides(const Sprite& _other) const
{
    if (collider && _other.collider)
    {
        return collider->Collides(*_other.collider); // @CHECK:
    }
    return false;
}
#pragma endregion