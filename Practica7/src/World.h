#pragma once
#include "litegfx.h"
#include "Sprite.h"
#include <list>
#include "Vec2.h"


class World
{
public:
    World(float _clearRed, float _clearGreen, float _clearBlue,
        const ltex_t* _background);

    ~World() { printf("Object World deleted.\n"); }

public:

protected:
    struct Background
    {
        const ltex_t* texture;
        float scrollRatio;
        Vec2 scrollSpeed;
        Vec2 scroll;
        Vec2 scrollOffset;
    } background;

private:
    float clearRed;
    float clearGreen;
    float clearBlue;
    Vec2 cameraPosition;
    std::list<Sprite*> spritesList;
    Vec2 windowSize;
    Vec2 mapSize;

public:
    void Update(float _deltaTime);
    void Draw(const Vec2& _screenSize);
    void AddSprite(Sprite& _sprite);
    void RemoveSprite(Sprite& _sprite);
    bool LoadMap(const char* _fileName, uint16_t _firstColId);
    bool MoveSprite(Sprite& _sprite, const Vec2& _amount);

#pragma region GETTERS_AND_SETTERS
    float GetClearRed() const;
    float GetClearGreen() const;
    float GetClearBlue() const;
    const ltex_t* GetBackground(size_t _layer) const;
    float GetScrollRatio(size_t _layer) const;
    const Vec2& GetScrollSpeed(size_t _layer) const;
    const Vec2& GetCameraPosition() const;
    const Vec2& GetWindowSize() const;
    const Vec2& GetMapSize() const; 

    void SetScrollRatio(size_t _layer, float _ratio);
    void SetScrollSpeed(size_t _layer, const Vec2& _speed);
    void SetCameraPosition(const Vec2& _position);
    void SetWindowSize(Vec2& _windowSize);
    void SetMapSize(Vec2& _mapSize);
#pragma  endregion

};