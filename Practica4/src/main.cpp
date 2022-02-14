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

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(WidthScreen, HeightScreen, "P3", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	lgfx_setup2d(WidthScreen, HeightScreen);

	while (!glfwWindowShouldClose(window))
	{
		DeltaTime = glfwGetTime();
		lgfx_clearcolorbuffer(0,0,0);
		lgfx_setblend(BLEND_ALPHA);
		
		
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

  return 0;
}