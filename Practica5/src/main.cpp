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
#include "CircleCollider.h"
#include "RectCollider.h"


ltex_t* LoadTexture(const char* _filename);

int main() {
#pragma region VAR_DECLARATIONS
    const int WidthScreen = 1280;
    const int HeightScreen = 960;
    double MouseX, MouseY;
    double DeltaTime = 0, LastTime = 0, UpdateTime = glfwGetTime();
    Vec2 CursorPosition;
    int leftMouseButton;
    int rightMouseButton;
    int middleMouseButton;

    Sprite* boxSprite = new Sprite();
    Sprite* beeSprite = new Sprite();
    Sprite* beeCursorSprite = new Sprite();
    Sprite* ballSprite = new Sprite();
    Sprite* rectSprite = new Sprite();
    Sprite* circleSprite = new Sprite();

    CircleCollider* circCollider = new CircleCollider();
    CircleCollider* ballCollider = new CircleCollider();
    RectCollider* rectCollider = new RectCollider();
#pragma endregion

    glfwInit();
    GLFWwindow* window = glfwCreateWindow(WidthScreen, HeightScreen, "P3", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    lgfx_setup2d(WidthScreen, HeightScreen);

    ltex_t* box = LoadTexture("data/box.png");
    ltex_t* bee = LoadTexture("data/bee.png");
    ltex_t* ball = LoadTexture("data/ball.png");
    ltex_t* circle = LoadTexture("data/circle.png");
    ltex_t* rect = LoadTexture("data/rect.png");

    while (!glfwWindowShouldClose(window))
    {
        LastTime = UpdateTime;
        UpdateTime = glfwGetTime();
        DeltaTime = UpdateTime - LastTime;

        leftMouseButton = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        rightMouseButton = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
        middleMouseButton = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);

        glfwGetCursorPos(window, &MouseX, &MouseY);
        CursorPosition.x = MouseX;
        CursorPosition.y = MouseY;

        lgfx_clearcolorbuffer(0, 0, 0);

        lgfx_setblend(BLEND_ALPHA);
        ballSprite->SetTexture(ball, WidthScreen * 0.25f, HeightScreen * 0.5f);
        ballSprite->SetPosition(Vec2(WidthScreen * 0.25f, HeightScreen * 0.5f));

        lgfx_setblend(BLEND_ALPHA);
        boxSprite->SetTexture(box, WidthScreen * 0.75f, HeightScreen * 0.5f);
        boxSprite->SetPosition(Vec2(WidthScreen * 0.75f - box->width * 0.5f, HeightScreen * 0.5f - box->height * 0.5f));

        lgfx_setblend(BLEND_ALPHA);
        beeSprite->SetTexture(bee, WidthScreen * 0.5f, HeightScreen * 0.5f);

        if (leftMouseButton == 1) // CIRCLE
        {
            circleSprite->SetTexture(circle, MouseX, MouseY);
            circleSprite->SetPosition(Vec2(MouseX, MouseY));
            if (circCollider->CheckCircleCircle(circleSprite->GetPosition(), circle->width * 0.5f,
                ballSprite->GetPosition(), ball->width * 0.5f))
            {
                printf("Circle - Ball\n");
            }
            else if (circCollider->CheckCircleRect(circleSprite->GetPosition(), circle->width * 0.5f,
                boxSprite->GetPosition(), Vec2(box->width, box->height)))
            {
                printf("Circle - Box\n");
            }
        }
        if (rightMouseButton == 1) // RECT
        {
            rectSprite->SetTexture(rect, MouseX, MouseY);
            rectSprite->SetPosition(Vec2(MouseX - rect->width * 0.5f, MouseY - rect->height * 0.5f));

            if (rectCollider->CheckRectRect(rectSprite->GetPosition(), Vec2(rect->width, rect->height),
                boxSprite->GetPosition(), Vec2(box->width, box->height)))
            {
                printf("Rect - Box\n");
            }
            else if (ballCollider->CheckCircleRect(ballSprite->GetPosition(), ball->width * 0.5f,
                rectSprite->GetPosition(), Vec2(rect->width, rect->height)))
            {
                printf("Rect - Ball\n");
            }
        }
        if (middleMouseButton == 1)
        {
            beeCursorSprite->SetTexture(bee, MouseX, MouseY);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
#pragma region DELETE
    delete boxSprite;
    boxSprite = nullptr;
    delete ballSprite;
    ballSprite = nullptr;
    delete beeSprite;
    beeSprite = nullptr;
    delete circleSprite;
    circleSprite = nullptr;
    delete rectSprite;
    rectSprite = nullptr;
    delete beeCursorSprite;
    beeCursorSprite = nullptr;
    delete ballCollider;
    ballCollider = nullptr;
    delete circCollider;
    circCollider = nullptr;
    delete rectCollider;
    rectCollider = nullptr;
#pragma endregion

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