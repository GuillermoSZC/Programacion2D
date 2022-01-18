#pragma once
#include "stb_truetype.h"
#include "vec2.h"

class Font
{
private:
	float height;

public:
	static Font* Load(const char* _Filename, float _Height);

	// GETTER
	float GetHeight() const;
	
	

};

