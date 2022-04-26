#pragma once
#include "Colliders.h"

class Sprite
{
public:
    Sprite() = default;
    Sprite(const ltex_t* _tex, int _hFrames, int _vFrames);
    ~Sprite() { printf("Sprite obj deleted.\n"); }

public:
    using CallbackFunc = void (*)(Sprite&, float);
    void SetCallback(CallbackFunc func);

protected:
    enum CollisionType
    {
        COLLISION_NONE,
        COLLISION_CIRCLE,
        COLLISION_RECT,
        COLLISION_PIXELS
    };

private:
    CallbackFunc callBackFunction;
    int hFrames, vFrames;
    int speed = 1;
    int collisionPixelSize;
    const ltex_t* tex;
    lblend_t mode;
    Vec2 position, scale, pivot, size;
    Collider* collider;
    float r, g, b, a;
    float spriteAngle;
    float FPS = 1, frame;
    float displayTimeSeconds;
    float time;
    unsigned char* buffer;
    bool xFlip;

public:
#pragma region GETTERS & SETTERS
    // GETTERS
    const ltex_t* GetTexture() const { return tex; }
    lblend_t GetBlend() const { return mode; }
    void* GetUserData();
    float GetRed() const { return r; }
    float GetGreen() const { return g; }
    float GetBlue() const { return b; }
    float GetAlpha() const { return a; }
    const Vec2& GetPosition() const { return position; }
    float GetAngle() const { return spriteAngle; }
    const Vec2& GetScale() const { return scale; }
    Vec2 GetSize() const;
    const Vec2& GetPivot() const;
    int GetHFrames() const { return hFrames; }
    int GetVframes() const { return vFrames; }
    float GetFPS() const { return FPS; }
    float GetCurrentFrame() const;
    int GetSpeed() { return speed; }
    CollisionType GetCollisionType() const;
    const Collider* GetCollider() const;

    // SETTERS
    void SetTexture(ltex_t* _tex, int _hFrames, int _vFrames);
    void SetBlend(lblend_t _Mode) { mode = _Mode; }
    void SetUserData(void* _Data);
    void SetColor(float _R, float _G, float _B, float _A);
    void SetPosition(const Vec2& _Position);
    void SetAngle(float _Angle);
    void SetPivot(const Vec2& _Pivot) { pivot = _Pivot; }
    void SetFPS(float _FPS);
    void SetCurrentFrame(float _Frame);
    void SetSpeed(int _Speed) { speed = _Speed; }
    void SetSize(float _width, float _height);
    void SetXFlip(bool _flip);
    void SetScale(Vec2& _scale);
    void SetCollisionType(CollisionType _type);
#pragma endregion

    void Update(float _deltaTime);
    void Draw() const;
    void UpdateCollidePosition(int _num);
    bool Collides(const Sprite& _other) const;

protected:


private:


};