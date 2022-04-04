#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION

#include <iostream>
#include <litegfx.h>
#include <glfw3.h>
#include "stb_image.h"
#include "Vec2.h"
#include<vector>
#include "Font.h"
#include"Sprite.h"
#include "CircleCollider.h"
#include "RectCollider.h"


ltex_t* LoadTexture(const char* _filename);

int main() {
#pragma region VAR_DECLARATIONS
    Vec2 SizeScreen(1280.f, 960.f);
    // const int WidthScreen = 1280;
    const int HeightScreen = 960;
    double MouseX, MouseY;
    double DeltaTime = 0, LastTime = 0, UpdateTime = glfwGetTime();
    Vec2 CursorPosition;

#pragma endregion

    glfwInit();
    GLFWwindow* window = glfwCreateWindow((int)SizeScreen.x, (int)SizeScreen.y, "P5", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    lgfx_setup2d((int)SizeScreen.x, (int)SizeScreen.y);


    while (!glfwWindowShouldClose(window))
    {
        lgfx_clearcolorbuffer(0, 0, 0);

        LastTime = UpdateTime;
        UpdateTime = glfwGetTime();
        DeltaTime = UpdateTime - LastTime;

        glfwGetCursorPos(window, &MouseX, &MouseY);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
