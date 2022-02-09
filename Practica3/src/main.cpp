#define LITE_GFX_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION

#include <iostream>
#include <litegfx.h>
#include <glfw3.h>
#include "stb_image.h"
#include "Vec2.h"
#include<vector>
#include"Font.h"

int main() {
	const int WidthScreen = 1280;
	const int HeightScreen = 960;
	double DeltaTime;
	std::vector<Font> VecFonts;

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(WidthScreen, HeightScreen, "P3", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	lgfx_setup2d(WidthScreen, HeightScreen);

	while (!glfwWindowShouldClose(window))
	{
		DeltaTime = glfwGetTime();
		lgfx_clearcolorbuffer(0,0,0);
		lgfx_setblend(BLEND_ALPHA);
		
		int SpawnText = rand() % 101;

		if (SpawnText == 0) // if SpawnText == 0 generate the text
		{
			int Rand2 = rand() % 2;
			Font* font = nullptr;

			if (Rand2 == 0)
			{
				font = Font::Load("data/SFSlapstickComic.ttf", 60);
			}
			else 
			{
				font = Font::Load("data/Orange.ttf", 60);
			}
			font->SetRGB(rand() % 256, rand() % 256, rand() % 256);
			font->SetPosition(vec2(0, (float)(rand() % HeightScreen + 1)));
			font->SetSpeed(20.f + (float)(rand() % 181));

			VecFonts.push_back(*font);
		}

		for (unsigned int i = 0; i < VecFonts.size(); i++)
		{
			lgfx_setcolor(VecFonts[i].GetR()/255, VecFonts[i].GetG()/255, VecFonts[i].GetB()/255, 1);
			VecFonts[i].draw("Hello, World!", VecFonts[i].GetPosition());
			VecFonts[i].UpdateXPosition(VecFonts[i].GetSpeed() / 50);
		} // draw fonts

		for (unsigned int i = 0; i < VecFonts.size(); i++)
		{
			if (VecFonts[i].GetPosition().x >= WidthScreen)
			{
				VecFonts.erase(VecFonts.begin() + i);
			} // delete the Font() when his x axis is equals to Width Screen
		}
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

  return 0;
}