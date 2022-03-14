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
    SetPosition(Vec2(_xPosition, _yPosition));
    ltex_drawrotsized(tex, _xPosition - tex->width * 0.5f, _yPosition - tex->height * 0.5f, 0, 0, 0, tex->width, tex->height, 0, 0, 1, 1);
}

void Sprite::DrawAnimTexture(float _xPosition, float _yPosition)
{  
    ltex_drawrotsized(tex, _xPosition - tex->width * 0.5f, _yPosition - tex->height * 0.5f, 0, 0, 0, tex->width, tex->height, 0, 0, 1, 1);
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
    case COLLISION_CIRCLE:
        if (collider != nullptr)
        {
            delete collider;
            collider = nullptr;
        }
        collider = new CircleCollider();
        collider->collisionType = 1;
        collider->circlePosition = position;
        collider->radius = tex->width * 0.5f;
        break;
    case COLLISION_RECT:
        if (collider != nullptr)
        {
            delete collider;
            collider = nullptr;
        }
        collider = new RectCollider();
        collider->collisionType = 2;
        collider->rectPosition = position;
        collider->rectSize = Vec2(tex->width, tex->height);
        break;
    case COLLISION_PIXELS:
        if (collider != nullptr)
        {
            delete collider;
            collider = nullptr;
        }
        collider = new PixelsCollider();
        iSize = tex->width * tex->height * 4;
        buffer = new unsigned char[iSize];
        ltex_getpixels(tex, buffer);
        collider->collisionType = 3;
        collider->pixelPosition = position;
        collider->pixelSize = Vec2(tex->width, tex->height);
        collider->pixels = buffer;
        break;
    }
}


void Sprite::UpdatePosition(int _num)
{
    switch (_num)
    {
    case 1:
        collider->circlePosition = position;
        break;
    case 2:
        collider->rectPosition = Vec2(position.x - tex->width * 0.5f, position.y - tex->height * 0.5f);
        break;
    case 3:
        collider->pixelPosition = Vec2(position.x - tex->width * 0.5f, position.y - tex->height * 0.5f);
        break;
    }
}

bool Sprite::Collides(const Sprite& _other) const
{
    if (collider && _other.collider)
    {
        return _other.collider->Collides(*collider); // @CHECK:
    }
    return false;
}
#pragma endregion