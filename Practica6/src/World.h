#pragma once
#include "litegfx.h"
#include <list>
#include "Sprite.h"
#include "Vec2.h"



class World
{
public:
    World() = default;
    World(float _clearRed, float _clearGreen, float _clearBlue,
          const ltex_t* _background0, const ltex_t* _background1,
          const ltex_t* _background2, const ltex_t* _background3);

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
    } background[4];

private:
    float clearRed;
    float clearGreen;
    float clearBlue;
    Vec2 cameraPosition;
    std::list<Sprite*> spritesList;

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