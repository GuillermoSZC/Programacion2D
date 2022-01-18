#define LITE_GFX_IMPLEMENTATION

#include <litegfx.h>
#include <glfw3.h>
#include <iostream>
#include "vec2.h"
#include <string>

int main() {
	double xpos, ypos;
	double xposMouse, yposMouse;
	int width = 1280, height = 960;
	float lado = 50.f;
	float angle = 0.f;
	float fDistance = 100.f;
	float delta;
	float textDist, textAngle;
	std::string cad;
	vec2 circleVec;
	vec2 cursorPosition;
	vec2 center((float)(width / 2.f), (float)(height / 2.f));

	GLFWwindow* window;

	glfwInit();
	

	glfwGetTime();

	if (!glfwInit())
	{
		printf("error init");
	}

	window = glfwCreateWindow(width, height, "P1", NULL, NULL);
	if (!window)
	{
		printf("error window");
	}

	while (!glfwWindowShouldClose(window))
	{

		delta = glfwGetTime();

		lgfx_setup2d(width, height);
		lgfx_clearcolorbuffer(1.f, 1.f, 1.f);

		lgfx_setcolor(0.8f, 0.2f, 0.f, 1.f);
		lgfx_drawrect((width / 2) - lado / 2, (height / 2) - lado / 2, lado, lado);
		
		glfwGetCursorPos(window, &xpos, &ypos);
		lgfx_setcolor(0.f, 0.9f, 0.5f, 1.f);
		lgfx_drawrect(xpos-lado/2, ypos-lado/2, lado, lado);

		angle = 32 * (PI / 180.f);

		xpos = xpos + cos(angle * delta) * fDistance;
		ypos = ypos + sin(angle * delta) * fDistance;

		circleVec.x = xpos;
		circleVec.y = ypos;
		
		lgfx_setcolor(0.8f, 0.f, 1.f, 1.f);
		lgfx_drawoval(circleVec.x - lado / 2, circleVec.y - lado / 2, lado, lado);

		glfwGetCursorPos(window, &xposMouse, &yposMouse);
		cursorPosition.x = xposMouse;
		cursorPosition.y = yposMouse;



		textDist = center.distance(cursorPosition);
		textAngle = cursorPosition.angle(circleVec);

		std::string title = "Distance: "
			+ std::to_string(textDist)
			+ ", Angle: "
			+ std::to_string(textAngle);

		glfwSetWindowTitle(window, title.c_str());

		glfwMakeContextCurrent(window);

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

