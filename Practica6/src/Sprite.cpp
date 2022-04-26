#include <iostream>
#include "litegfx.h"
#include "Vec2.h"
#include "Sprite.h"
#include "stb_image.h"

#pragma region Sprite

Sprite::Sprite(const ltex_t* _tex, int _hFrames, int _vFrames)
{
    tex = _tex;
    hFrames = _hFrames;
    vFrames = _vFrames;
    pivot = Vec2(0.5, 0.5);
    size.x = tex->width / hFrames;
    size.y = tex->height / vFrames;
}

void Sprite::SetTexture(ltex_t* _tex, int _hFrames, int _vFrames)
{
    tex = _tex;
    hFrames = _hFrames;
    vFrames = _vFrames;
    size.x = tex->width / hFrames;
    size.y = tex->height / vFrames;
}

void Sprite::SetColor(float _R, float _G, float _B, float _A)
{
    r = _R;
    g = _G;
    b = _B;
    a = _A;
}

void Sprite::Update(float _deltaTime)
{
    if (callBackFunction)
    {
        (*callBackFunction)(*this, _deltaTime);
    }

    time += _deltaTime;

    if (time >= (1.f / FPS))
    {
        time = 0;
        float temp = GetCurrentFrame();

        if ((temp + 1) > FPS)
        {
            SetCurrentFrame(1);
        }
        else
        {
            SetCurrentFrame(temp + 1);
        }
    }
}

void Sprite::Draw() const
{
    lgfx_setblend(mode);

    float currentFrame = frame;

    int xTex = tex->width;
    int yTex = tex->height;

    float xFrame = xTex / hFrames;
    float yFrame = yTex / vFrames;

    float u0 = ((currentFrame * xFrame) - xFrame) / xTex;
    float v0 = ((currentFrame * yFrame) - yFrame) / yTex;

    float u1 = (currentFrame * xFrame) / xTex;
    float v1 = (currentFrame * yFrame) / yTex;

    if (xFlip)
    {
        float temp = u0;
        u0 = u1;
        u1 = temp;
    }

    lgfx_setcolor(r, g, b, 1);
    const ltex_t* texture = tex;
    ltex_drawrotsized(texture, position.x, position.y, spriteAngle, pivot.x, pivot.y, size.x, size.y, u0, v0, u1, v1);
}

void Sprite::SetCallback(CallbackFunc func)
{
    callBackFunction = func;
}

void Sprite::SetSize(float _width, float _height)
{
    size.x = _width;
    size.y = _height;
}

void Sprite::SetXFlip(bool _flip)
{
    xFlip = _flip;
}

Vec2 Sprite::GetSize() const
{
    return {size.x * scale.x, size.y * scale.y};
}

float Sprite::GetCurrentFrame() const
{
    return frame;
}

void Sprite::SetFPS(float _FPS)
{
    FPS = _FPS;
}

void Sprite::SetCurrentFrame(float _Frame)
{
    frame = _Frame;
}

void Sprite::SetPosition(const Vec2& _Position)
{
    position = _Position;
}

void Sprite::SetAngle(float _Angle)
{
    spriteAngle = _Angle;
}

void Sprite::SetScale(Vec2& _scale)
{
    scale = _scale;
}
#pragma endregion

#pragma region Collider

void Sprite::SetCollisionType(CollisionType _type)
{
    if (collider)
    {
        delete collider;
        collider = nullptr;
    }
    if (_type == Sprite::COLLISION_CIRCLE)
    {
        collider = new CircleCollider();
        collider->circlePosition = position;
        collider->radius = tex->width * 0.5f;
    }
    else if (_type == Sprite::COLLISION_RECT)
    {
        collider = new RectCollider();
        collider->rectPosition = position;
        collider->rectSize = Vec2(tex->width, tex->height);
    }
    else if (_type == Sprite::COLLISION_PIXELS)
    {
        collider = new PixelsCollider();
        collisionPixelSize = tex->width * tex->height;
        buffer = new unsigned char[tex->width * tex->height * 4];
        ltex_getpixels(tex, buffer);
        collider->pixelPosition = position;
        collider->pixelSize = Vec2(tex->width, tex->height);
        collider->pixels = buffer;
    }
}


void Sprite::UpdateCollidePosition(int _num)
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
        return _other.collider->Collides(*collider);
    }
    return false;
}




#pragma endregion