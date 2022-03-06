#pragma once

#include "stb_truetype.h"

class Font
{
private:
	Font() { }
	Font(float _Height, float _Width, ltex_t* _Tex, float _R, float _G, float _B, float _Speed, Vec2 _Position, stbtt_bakedchar* _CharData)
	{
		Height = _Height;
		Width = _Width;
		Tex = _Tex;
		r = _R;
		g = _G;
		b = _B;
		Speed = _Speed;
		Position = _Position;
		CharData = _CharData;
	}

private:
	float Height;
	float Width;
	ltex_t* Tex;
	float r, g, b;
	float Speed;
	Vec2 Position;
	stbtt_bakedchar* CharData;

public:
	~Font() { printf("Font object deleted.."); }

	// GETTER
	float GetHeight() const { return Height; }
	float GetWidth() const { return Width; }
	ltex_t* GetTex() { return Tex; }
	float GetR() { return r; }
	float GetG() { return g; }
	float GetB() { return b; }
	float GetSpeed() { return Speed; }
	Vec2 GetPosition() { return Position; }
	stbtt_bakedchar* GetCharData() { return CharData; }

	// SETTER
	void SetHeight(float _Height) { Height = _Height; }
	void SetWidth(float _Width) { Width = _Width; }
	void SetTex(ltex_t* _Tex) { Tex = _Tex; }
	void SetR(float _R) { r = _R; }
	void SetG(float _G) { g = _G; }
	void SetB(float _B) { b = _B; }
	void SetSpeed(float _Speed) { Speed = _Speed; }
	void SetPosition(Vec2 _Position) { Position = _Position; }
	void SetCharData(stbtt_bakedchar* _CharData) { CharData = _CharData; }

	// FUNCTIONS
	static Font* Load(const char* _Filename, float _Height);
	void draw(const char* _text, Vec2 _Position) const; 
	Vec2 getTextSize(const char* _text) const;
	void SetRGB(float _R, float _G, float _B) { r = _R;  g = _G;  b = _B; }
	void UpdateXPosition(float _PosX) { Position.x += _PosX; }
};

