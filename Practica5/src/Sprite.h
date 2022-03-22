#pragma once
#include "Colliders.h"

class Sprite
{
private:
    int hFrames, vFrames;
    const ltex_t* tex;
    lblend_t mode;
    float r, g, b, a;
    float angle;
    Vec2 position, scale, pivot, size;
    float FPS, frame;
    int speed = 1;
    float displayTimeSeconds;
    Collider* collider;
    unsigned char* buffer;
    int iSize;
    Vec2 animSize = Vec2(1, 1);

public:
    enum CollisionType
    {
        COLLISION_NONE,
        COLLISION_CIRCLE,
        COLLISION_RECT,
        COLLISION_PIXELS
    };

public:
    Sprite() { }
    ~Sprite() { printf("Sprite obj deleted.\n"); }

    typedef void(*CallbackFunc)(Sprite& _Sprite, float _DeltaTime);

    Sprite(const ltex_t* _Tex) : hFrames(1), vFrames(1)
    {
        tex = _Tex;
    }
#pragma region GETTERS & SETTERS
    // GETTERS
    const ltex_t* GetTexture() const { return tex; }
    lblend_t GetBlend() const;
    void* GetUserData();
    float GetRed() const { return r; }
    float GetGreen() const { return g; }
    float GetBlue() const { return b; }
    float GetAlpha() const { return a; }
    const Vec2& GetPosition() const { return position; }
    float GetAngle() const { return angle; }
    const Vec2& GetScale() const { return scale; }
    Vec2 GetSize() const;
    const Vec2& GetPivot() const;
    int GetHFrames() const { return hFrames; }
    int GetVframes() const { return vFrames; }
    float GetFPS() const { return FPS; }
    float GetCurrentFrame() const;
    int GetSpeed() { return speed; }

    // SETTERS
    void SetTexture(ltex_t* _tex);
    void DrawTexture(float _xPosition, float _yPosition);
    void SetBlend(lblend_t _Mode) { mode = _Mode; }
    void SetUserData(void* _Data);
    void SetColor(float _R, float _G, float _B, float _A);
    void SetPosition(const Vec2& _Position);
    void SetAnimPosition(const Vec2& _Position);
    void SetAngle(float _Angle);
    void SetPivot(const Vec2& _Pivot) { pivot = _Pivot; }
    void SetFPS(float _FPS);
    void SetCurrentFrame(float _Frame);
    void SetSpeed(int _Speed) { speed = _Speed; }
    void SetSize(float _width, float _height);

#pragma endregion
    void SetCollisionType(CollisionType _type);
    CollisionType GetCollisionType() const;
    void UpdatePosition(int _num);
    const Collider* GetCollider() const;
    bool Collides(const Sprite& _other) const;
    void SetScale(float _scale);

    // FUNCTIONS 
    void Update(float _DeltaTime);
    void Draw() const;
    void SetCallback(CallbackFunc func);


};