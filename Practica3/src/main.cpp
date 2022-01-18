#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <litegfx.h>
#include <glfw3.h>
#include "stb_image.h"
#include "Vec2.h"
#include "stb_truetype.h"

int main() {
	double xpos, ypos;
	double xposMouse, yposMouse;
	const int width = 1280;
	const int height = 960;
	float delta;
	float min_dregree = -10.f, max_degree = 10.f, degree_ratio = 10.f;
	float min_scale = 0.8f, max_scale = 1.2f, scale_ratio = 0.5f;
	float degree = 0.f, scale = 0.f;
	vec2 cursorPosition;

	glfwInit();
	
	if (!glfwInit())
	{
		printf("error init");
	}
	
	GLFWwindow* window = glfwCreateWindow(width, height, "P2", nullptr, nullptr);
	if (!window)
	{
		printf("error window");
	}

	glfwMakeContextCurrent(window);
	lgfx_setup2d(width, height);
	// renderizo alpha buffer
		stbtt_BakeFontBitmap("Orange.ttf", 0, 24, );

	while (!glfwWindowShouldClose(window))
	{
		delta = glfwGetTime();

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
	}
	glfwTerminate();

  return 0;
}




