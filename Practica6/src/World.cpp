#include "World.h"

World::World(float _clearRed, float _clearGreen, float _clearBlue,
             const ltex_t* _background0, const ltex_t* _background1,
             const ltex_t* _background2, const ltex_t* _background3) :
             clearRed(_clearRed), clearBlue(_clearBlue), clearGreen(_clearGreen)
{
    background[0].texture = _background0;
    background[1].texture = _background1;
    background[2].texture = _background2;
    background[3].texture = _background3;
}

#pragma region FUNCTIONS
void World::Update(float _deltaTime)
{
    for (auto& sprite : background)
    {
        sprite.scrollOffset.x = sprite.scrollOffset.x + sprite.scrollSpeed.x * _deltaTime;
        sprite.scrollOffset.y = sprite.scrollOffset.y + sprite.scrollSpeed.y * _deltaTime;
        sprite.scroll.x = (cameraPosition.x * sprite.scrollRatio + sprite.scrollOffset.x) / sprite.texture->width;
        sprite.scroll.y = (cameraPosition.y * sprite.scrollRatio + sprite.scrollOffset.y) / sprite.texture->height;
    }

    for (Sprite* sprite : spritesList)
    {
        sprite->Update(_deltaTime);
    }
}

void World::Draw(const Vec2& _screenSize)
{
    lgfx_clearcolorbuffer(clearRed, clearGreen, clearBlue);
    lgfx_setorigin(cameraPosition.x, cameraPosition.y);

    for (int i = 3; i >= 0; --i)
    {
        float u1 = background[i].scroll.x + _screenSize.x / background[i].texture->width;
        float v1 = background[i].scroll.y + _screenSize.y / background[i].texture->height;
        ltex_drawrotsized(background[i].texture, cameraPosition.x, cameraPosition.y, 0.f, 0.f, 0.f, _screenSize.x, _screenSize.y,
            background[i].scroll.x, background[i].scroll.y, u1, v1);
    }

    for (Sprite* sprite : spritesList)
    {
        sprite->Draw();
    }
}

void World::AddSprite(Sprite& _sprite)
{
    spritesList.push_back(&_sprite);
}

void World::RemoveSprite(Sprite& _sprite)
{
    spritesList.remove(&_sprite);
}
#pragma endregion

#pragma region GETTERS_AND_SETTERS
float World::GetClearRed() const
{
    return clearRed;
}

float World::GetClearGreen() const
{
    return clearGreen;
}

float World::GetClearBlue() const
{
    return clearBlue;
}

const ltex_t* World::GetBackground(size_t _layer) const
{
    if (_layer >= 0 && _layer < 4)
    {
        return background[_layer].texture;
    }
    return nullptr;
}

float World::GetScrollRatio(size_t _layer) const
{
    if (_layer >= 0 && _layer < 4)
    {
        return background[_layer].scrollRatio;
    }
    return 0.f;
}

const Vec2& World::GetScrollSpeed(size_t _layer) const
{
    if (_layer >= 0 && _layer < 4)
    {
        return background[_layer].scrollSpeed;
    }

    return Vec2(0.f, 0.f);
}

const Vec2& World::GetCameraPosition() const
{
    return cameraPosition;
}

void World::SetScrollRatio(size_t _layer, float _ratio)
{
    if (_layer >= 0 && _layer < 4)
    {
        background[_layer].scrollRatio = _ratio;
    }
}

void World::SetScrollSpeed(size_t _layer, const Vec2& _speed)
{
    if (_layer >= 0 && _layer < 4)
    {
        background[_layer].scrollSpeed = _speed;
    }
}

void World::SetCameraPosition(const Vec2& _position)
{
    cameraPosition = _position;
}
#pragma endregion