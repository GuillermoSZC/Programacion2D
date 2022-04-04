#include "World.h"

World::World() : clearRed(0.15f), clearGreen(0.15f), clearBlue(0.15f),
                 back0(nullptr), back1(nullptr), back2(nullptr), back3(nullptr),
                 scrollSpeed(0.f, 0.f), cameraPosition(0.f, 0.f), scrollRatio(0.f)
{

}

World::~World()
{
    printf("Object world deleted.\n");
}
#pragma region FUNCTIONS
void World::Update(float _deltaTime)
{

}

void World::Draw(const Vec2& _screenSize)
{

}

void World::AddSprite(Sprite& _sprite)
{

}

void World::RemoveSprite(Sprite& _sprite)
{

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
    return nullptr;
}

float World::GetScrollRatio(size_t _layer) const
{
    return scrollRatio;
}

const Vec2& World::GetScrollSpeed(size_t _layer) const
{
    return scrollSpeed;
}

const Vec2& World::GetCameraPosition() const
{
    return cameraPosition;
}

void World::SetScrollRatio(size_t _layer, float _ratio)
{
    scrollRatio = _ratio;
}

void World::SetScrollSpeed(size_t _layer, const Vec2& _speed)
{
    scrollSpeed = _speed;
}

void World::SetCameraPosition(const Vec2& _position)
{
    cameraPosition = _position;
}
#pragma endregion