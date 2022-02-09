#include <iostream>
#include "litegfx.h"
#include "vec2.h"
#include "Font.h"

Font* Font::Load(const char* _Filename, float _Height)
{
	FILE* File = nullptr;
	size_t Result;
	int iSize = 512;
	unsigned char* Pixels = new unsigned char[iSize * iSize];
	stbtt_bakedchar* CharData = new stbtt_bakedchar[iSize * 0.5f];

	fopen_s(&File, _Filename, "rb");

	if (File != nullptr)
	{
		fseek(File, 0 , SEEK_END);
		long lSize = ftell(File);
		fseek(File, 0, SEEK_SET);
		char* Buffer = new char[lSize];
		Result = fread(Buffer, sizeof(char), lSize, File);
		fclose(File);
		unsigned char* ptrBuffer = reinterpret_cast<unsigned char*>(Buffer);

		int BFB = stbtt_BakeFontBitmap(ptrBuffer, 0, _Height, Pixels, iSize, iSize, 0, 256, CharData);

		unsigned char* ColorBuffer = new unsigned char[4 * iSize * iSize];
		
		for (int i = 0; i < (4 * iSize * iSize); i++)
		{
			ColorBuffer[i] = 255;
			if (i % 4 == 0 && i > 0)
			{
				ColorBuffer[i - 1] = Pixels[i / 4];
			}
		}

		ltex_t* Tex = ltex_alloc(iSize, iSize, 0);
		ltex_setpixels(Tex, ColorBuffer);

		Font* objFont = new Font(_Height, _Height, Tex, 0, 0, 0,  0, vec2(0,0), CharData);
		return objFont;
	}
	return nullptr;
}

vec2 Font::getTextSize(const char* _text) const
{
	return vec2();
}

void Font::draw(const char* _text, vec2 _Position) const
{
	float x = _Position.x;
	float y = _Position.y;
	stbtt_aligned_quad* q = new stbtt_aligned_quad();

	for (int i = 0; i < 14; i++)
	{
		stbtt_GetBakedQuad(CharData, Tex->width, Tex->height, int(_text[i]), &x, &y, q, true);
		ltex_drawrotsized(Tex, x, y, 0, 1.0f, 0.5f, (q->x1 - q->x0), (q->y1 - q->y0), q->s0, q->t0, 
			q->s1, q->t1);
	}
}