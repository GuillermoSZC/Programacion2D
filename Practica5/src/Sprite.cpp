#include <iostream>
#include "litegfx.h"
#include "Vec2.h"
#include "Sprite.h"

#pragma region Sprite
void Sprite::SetTexture(const ltex_t* _Tex/*, int _HFrames, int _VFrames*/)
{
	ltex_drawrotsized(_Tex, position.x, position.y, angle, 0, 0,
		_Tex->width / 8.f * 2.f, _Tex->height * 2.f, 0.125f * GetCurrentFrame(), 0.f, 0.125f * GetCurrentFrame() + 0.125f, 1.f);

	// hFrames = _HFrames;
	// vFrames = _VFrames;
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
	position.x += (_Position.x - 50 - position.x) / 128;
	position.y += (_Position.y - 50 - position.y) / 128;
}

void Sprite::SetAngle(float _Angle) 
{ 
	angle += _Angle; 
}
#pragma endregion

#pragma region Collider
bool Sprite::Collides(const Sprite& _other) const
{

	return false;
}
#pragma endregion