#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION

#include <iostream>
#include <litegfx.h>
#include <glfw3.h>
#include "stb_image.h"
#include "Vec2.h"
#include<vector>
#include"Font.h";
#include"Sprite.h"

ltex_t* LoadTexture(const char* _filename);

int main() {
	const int WidthScreen = 1280;
	const int HeightScreen = 960;
	double MouseX, MouseY;
	double DeltaTime = 0, LastTime = 0, UpdateTime = glfwGetTime();
	vec2 CursorPosition;

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(WidthScreen, HeightScreen, "P3", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	lgfx_setup2d(WidthScreen, HeightScreen);

	ltex_t* Bee = LoadTexture("data/bee_anim.png");
	Sprite* sprite = new Sprite();
	
	while (!glfwWindowShouldClose(window))
	{
		LastTime = UpdateTime;
		UpdateTime = glfwGetTime();
		DeltaTime = UpdateTime - LastTime;

		glfwGetCursorPos(window, &MouseX, &MouseY);
		CursorPosition.x = MouseX;
		CursorPosition.y = MouseY;

		sprite->SetPosition(vec2(CursorPosition.x, CursorPosition.y));
		if (sprite->GetPosition().x > CursorPosition.x && sprite->GetAngle() <= 15.f)
		{
			sprite->SetAngle(32 * DeltaTime);
		}
		if (sprite->GetPosition().x < CursorPosition.x && sprite->GetAngle() >= -15.f)
		{
			sprite->SetAngle(-32 * DeltaTime);
		}
		if (sprite->GetPosition().x == CursorPosition.x && sprite->GetPosition().y == CursorPosition.y)
		{
			if (sprite->GetAngle() > 0)
			{
				sprite->SetAngle(-32 * DeltaTime);
			}
			else if (sprite->GetAngle() < 0)
			{
				sprite->SetAngle(32 * DeltaTime);
			}
		}
		sprite->Update(DeltaTime);

		lgfx_clearcolorbuffer(0,0,0);
		lgfx_setblend(BLEND_ALPHA);
		sprite->SetTexture(Bee);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

  return 0;
}

ltex_t* LoadTexture(const char* _filename)
{
	int* x = new int;
	int* y = new int;

	unsigned char* buffer = stbi_load(_filename, x, y, nullptr, 4);
	ltex_t* tex_ = ltex_alloc(*x, *y, 1);

	ltex_setpixels(tex_, buffer);
	stbi_image_free(buffer);

	return tex_;
}