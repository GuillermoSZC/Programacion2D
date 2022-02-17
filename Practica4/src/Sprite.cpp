#include <iostream>
#include "litegfx.h"
#include "vec2.h"
#include "Sprite.h"


void Sprite::SetTexture(const ltex_t* _Tex/*, int _HFrames, int _VFrames*/)
{
	ltex_drawrotsized(_Tex, position.x, position.y, angle, 0, 0,
		_Tex->width / 8 * 2, _Tex->height * 2, 0.125 * GetCurrentFrame(), 0, 0.125 * GetCurrentFrame() + 0.125, 1);

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

void Sprite::SetPosition(const vec2& _Position) 
{ 
	position.x += (_Position.x - 50 - position.x) / 128;
	position.y += (_Position.y - 50 - position.y) / 128;
}

void Sprite::SetAngle(float _Angle) 
{ 
	angle += _Angle; 
}