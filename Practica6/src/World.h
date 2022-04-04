#pragma once
#include "litegfx.h"
#include "Sprite.h"
#include "Vec2.h"

class World
{
public:
    World();
    ~World();

public:


protected:


private:
    float clearRed;
    float clearGreen;
    float clearBlue;
    const ltex_t* back0;
    const ltex_t* back1;
    const ltex_t* back2;
    const ltex_t* back3;
    Vec2 scrollSpeed;
    Vec2 cameraPosition;
    float scrollRatio;

public:
    void Update(float _deltaTime);
    void Draw(const Vec2& _screenSize);
    void AddSprite(Sprite& _sprite);
    void RemoveSprite(Sprite& _sprite);

#pragma region GETTERS_AND_SETTERS
    float GetClearRed() const;
    float GetClearGreen() const;
    float GetClearBlue() const;
    const ltex_t* GetBackground(size_t _layer) const;
    float GetScrollRatio(size_t _layer) const;
    const Vec2& GetScrollSpeed(size_t _layer) const;
    const Vec2& GetCameraPosition() const;

    void SetScrollRatio(size_t _layer, float _ratio);
    void SetScrollSpeed(size_t _layer, const Vec2& _speed);
    void SetCameraPosition(const Vec2& _position);
#pragma  endregion

};