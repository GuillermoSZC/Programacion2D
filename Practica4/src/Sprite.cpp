#include <iostream>
#include "litegfx.h"
#include "vec2.h"
#include "Sprite.h"


void Sprite::SetTexture(const ltex_t* _Tex, int _HFrames, int _VFrames)
{
	tex = _Tex;
	hFrames = _HFrames;
	vFrames = _VFrames;
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
	if (!nullptr)
	{

	}
}



