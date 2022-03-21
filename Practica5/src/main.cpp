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
    bool collides, val(false);
    Vec2 CursorPosition;
    int collisionType = 1;

    Sprite* boxSprite = new Sprite();
    Sprite* beeSprite = new Sprite();
    Sprite* ballSprite = new Sprite();
    Sprite* cursorSprite = new Sprite();
#pragma endregion

    glfwInit();
    GLFWwindow* window = glfwCreateWindow(WidthScreen, HeightScreen, "P5", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    lgfx_setup2d(WidthScreen, HeightScreen);

    ltex_t* box = LoadTexture("data/box.png");
    ltex_t* bee = LoadTexture("data/bee.png");
    ltex_t* ball = LoadTexture("data/ball.png");
    ltex_t* circle = LoadTexture("data/circle.png");
    ltex_t* rect = LoadTexture("data/rect.png");

    boxSprite->SetTexture(box);
    boxSprite->SetPosition(Vec2(WidthScreen * 0.75f - box->width * 0.5f, HeightScreen * 0.5f - box->height * 0.5f));
    boxSprite->SetCollisionType(Sprite::COLLISION_RECT);

    beeSprite->SetTexture(bee);
    beeSprite->SetPosition(Vec2(WidthScreen * 0.5f - bee->width * 0.5f, HeightScreen * 0.5f - bee->height * 0.5f));
    beeSprite->SetCollisionType(Sprite::COLLISION_PIXELS);

    ballSprite->SetTexture(ball);
    ballSprite->SetPosition(Vec2(WidthScreen * 0.25f, HeightScreen * 0.5f));
    ballSprite->SetCollisionType(Sprite::COLLISION_CIRCLE);

    cursorSprite->SetTexture(circle); // @TODO: Meter un puntero por defecto
    cursorSprite->SetCollisionType(Sprite::COLLISION_CIRCLE);

    while (!glfwWindowShouldClose(window))
    {
        lgfx_clearcolorbuffer(0, 0, 0);

        LastTime = UpdateTime;
        UpdateTime = glfwGetTime();
        DeltaTime = UpdateTime - LastTime;

        glfwGetCursorPos(window, &MouseX, &MouseY);
        

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) // CIRCLE
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            cursorSprite->SetTexture(circle);
            collisionType = 1;
            cursorSprite->SetCollisionType(Sprite::COLLISION_CIRCLE);
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)) // RECT
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            cursorSprite->SetTexture(rect);
            collisionType = 2;
            cursorSprite->SetCollisionType(Sprite::COLLISION_RECT);

        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE)) // BEE
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            cursorSprite->SetTexture(bee);
            collisionType = 3;
            cursorSprite->SetCollisionType(Sprite::COLLISION_PIXELS);
        }

        cursorSprite->UpdatePosition(collisionType);

        lgfx_setblend(BLEND_ALPHA);

        collides = cursorSprite->Collides(*boxSprite);
        if (collides)
        {
            val = true;
            lgfx_setcolor(1, 0, 0, 1);
        }
        else
        {
            lgfx_setcolor(1, 1, 1, 1);
        }
        boxSprite->DrawAnimTexture(WidthScreen * 0.75f, HeightScreen * 0.5f);


       collides = cursorSprite->Collides(*beeSprite);
        if (collides)
        {
            val = true;
            lgfx_setcolor(1, 0, 0, 1);
        }
        else
        {
            lgfx_setcolor(1, 1, 1, 1);
        }
        beeSprite->DrawTexture(WidthScreen * 0.5f, HeightScreen * 0.5f);

        collides = cursorSprite->Collides(*ballSprite);
        if (collides)
        {
            val = true;
            lgfx_setcolor(1, 0, 0, 1);
        }
        else
        {
            lgfx_setcolor(1, 1, 1, 1);
        }
        ballSprite->DrawTexture(WidthScreen * 0.25f, HeightScreen * 0.5f);
        
        if (val)
        {
            lgfx_setcolor(1, 0, 0, 1);
        }
        else
        {
            lgfx_setcolor(1, 1, 1, 1);
        }
        cursorSprite->DrawTexture(MouseX, MouseY);
        val = false;


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