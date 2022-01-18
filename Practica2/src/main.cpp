#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <litegfx.h>
#include <glfw3.h>
#include "stb_image.h"
#include "Vec2.h"

ltex_t* loadTexture(const char* _filename);
float pingpong(float _start, float _stop, float _frequency);

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
	// cargo las cuatro imagenes
	ltex_t* wall = loadTexture("data/wall.jpg");
	ltex_t* fire = loadTexture("data/fire.png");
	ltex_t* grille = loadTexture("data/grille.png");
	ltex_t* light = loadTexture("data/light.png");

	while (!glfwWindowShouldClose(window))
	{
		delta = glfwGetTime();
		// calculo la posicion del cursor las guardo en el x e y del vector cursorPosition
		glfwGetCursorPos(window, &xposMouse, &yposMouse);
		cursorPosition.x = xposMouse;
		cursorPosition.y = yposMouse;

		lgfx_clearcolorbuffer(1.f, 1.f, 1.f);
		// establezco los tipos de mezclados de colores con las funciones lgfx_setblend
		// y dibujo cada imagen con las funciones ltex_drawrotsized y ltex_draw
		lgfx_setblend(BLEND_SOLID);
		ltex_drawrotsized(wall, 0, 0, 0, 0, 0, width, height, 0, 0, width / wall->width, height / wall->height);

		degree = pingpong(min_dregree, max_degree, degree_ratio * delta);
		scale = pingpong(min_scale, max_scale, scale_ratio * delta);

		lgfx_setblend(BLEND_ADD);
		ltex_drawrotsized(fire, cursorPosition.x, cursorPosition.y, degree, 0.5, 0.5, fire->width * scale, fire->height * scale, 0, 0, 1, 1);

		lgfx_setblend(BLEND_ALPHA);
		ltex_drawrotsized(grille, 0, 0, 0, 0, 0, width, height, 0, 0, width / grille->width, height / grille->height);

		lgfx_setblend(BLEND_MUL);
		ltex_draw(light, cursorPosition.x - light->width / 2, cursorPosition.y - light->height / 2);

		// creo cuatro rectangulos del tamaño de mi pantalla arriba, abajo y a los lados para crear los 'bordes' negros
		// su posicion va variando según la posicion del cursor
		lgfx_setcolor(0.f, 0.f, 0.f, 1.f);
		lgfx_drawrect(cursorPosition.x + light->width / 2, 0, 1920, 1080);
		lgfx_drawrect(cursorPosition.x - light->width / 2, 0, -1920, 1080);
		lgfx_drawrect(0, cursorPosition.y + light->height / 2, 1920, 1080);
		lgfx_drawrect(0, cursorPosition.y - light->height / 2, 1920, -1080);
		lgfx_setcolor(1.f, 1.f, 1.f, 1.f);

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

ltex_t* loadTexture(const char* _filename)
{
	int* x = new int;
	int* y = new int;

	unsigned char* buffer = stbi_load(_filename, x, y, nullptr, 4);
	ltex_t* tex_ = ltex_alloc(*x, *y, 1);

	ltex_setpixels(tex_, buffer);
	stbi_image_free(buffer);

	return tex_;
}

float pingpong(float _start, float _stop, float _freq)
{
	float distance = _stop - _start;
	float vAbsoluto = sqrtf(_freq * _freq);
	float mod = fmod(vAbsoluto, distance);

	if (static_cast<int>(vAbsoluto / distance) % 2 == 0)
	{
		return _start + mod;
	}
	else
	{
		return _stop - mod;
	}
}
