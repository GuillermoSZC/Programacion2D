#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION

#include <iostream>
#include <glfw3.h>
#include "stb_image.h"
#include "Vec2.h"
#include<vector>
#include "World.h"
#include "Font.h"
#include"Sprite.h"
#include "CircleCollider.h"
#include "RectCollider.h"

#define FIXED_TICK_60   1.f / 60.f
#define WINDOW_SIZE  Vec2(1000.f, 800.f)

#pragma region INIT_AUX_FUNCTIONS
void BeeBehavior(Sprite& _spriteref, float _deltatime);
ltex_t* LoadTexture(const char* filename);
float Clamp(float _value, float _min, float _max);
#pragma endregion

Vec2 cursorPosition = Vec2(0.f, 0.f);

int main() {
#pragma region VAR_DECLARATIONS
    double mouseX, mouseY;
    double deltaTime = 0, lastTime = 0, currentTime = glfwGetTime();
    Vec2 cameraPosition = Vec2(0.f, 0.f);
    float camera;
#pragma endregion
#pragma region INIT_GLFW_&_VARIABLES
    if (!glfwInit())
    {
        printf("Error to init GLFW.\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow((int)WINDOW_SIZE.x, (int)WINDOW_SIZE.y, "P6", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    lgfx_setup2d((int)WINDOW_SIZE.x, (int)WINDOW_SIZE.y);

    ltex_t* beeTexture = LoadTexture("data/bee_anim.png");
    auto* bee = new Sprite(beeTexture, 8, 1);
    if (!bee)
    {
        printf("Error Bee NULL.\n");
        return -1;
    }

    bee->SetFPS(25.f);
    bee->SetCallback(&BeeBehavior);
    bee->SetBlend(BLEND_ALPHA);
    bee->SetScale(Vec2(1.f, 1.f));
    bee->SetColor(1.f, 1.f, 1.f, 1.f);
    bee->SetPosition(Vec2(WINDOW_SIZE.x * 0.5f, WINDOW_SIZE.y * 0.5f));
    bee->SetAngle(0.f);

    ltex_t* clouds = LoadTexture("data/clouds.png");
    ltex_t* level = LoadTexture("data/level.png");
    ltex_t* trees1 = LoadTexture("data/trees1.png");
    ltex_t* trees2 = LoadTexture("data/trees2.png");

    auto* world = new World(0.6f, 0.8f, 5.f, level, trees1, trees2, clouds);

    world->SetScrollRatio(0, 2.f);
    world->SetScrollRatio(1, 1.8f);
    world->SetScrollRatio(2, 1.4f);
    world->SetScrollRatio(3, 1.f);
    world->SetScrollSpeed(3, Vec2(-200.f, -100.f));
    world->AddSprite(*bee);
#pragma endregion

    while (!glfwWindowShouldClose(window)) // ~ Game loop
    {
        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        glfwGetCursorPos(window, &mouseX, &mouseY);
        cursorPosition = Vec2(mouseX + world->GetCameraPosition().x, mouseY + world->GetCameraPosition().y);

        lgfx_clearcolorbuffer(0, 0, 0);

        while (deltaTime >= FIXED_TICK_60)
        {
            deltaTime -= FIXED_TICK_60;
            world->Update(FIXED_TICK_60);
        }

        world->Draw(WINDOW_SIZE);
        camera = Clamp(bee->GetPosition().x - (WINDOW_SIZE.x * 0.5f), 0.f, world->GetBackground(0)->width - WINDOW_SIZE.y);

        world->SetCameraPosition(Vec2(camera, 0.f));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

#pragma region AUX_FUNCTIONS
void BeeBehavior(Sprite& _sprite, float _deltaTime)
{
    float rotate = 0.f;
    bool flip = true;
    float angle = 0.f;
    Vec2 direction;
    Vec2 beePos;
    Vec2 newPos;
    Vec2 normDir;

    beePos = _sprite.GetPosition();

    direction.x = cursorPosition.x - beePos.x;
    direction.y = cursorPosition.y - beePos.y;

    angle = _sprite.GetAngle();

    if (direction.AbsoluteVal(direction) >= 8.f)
    {
        normDir = direction.Normal(direction);

        newPos = beePos;

        newPos.x = beePos.x + (normDir.x * (128 * _deltaTime));
        newPos.y = beePos.y + (normDir.y * (128 * _deltaTime));

        if (cursorPosition.x >= newPos.x)
        {
            flip = false;
        }

        _sprite.SetXFlip(flip);

        if (abs(cursorPosition.y - newPos.y) < 30)
        {
            rotate = 0;
        }
        else if (cursorPosition.y > newPos.y)
        {
            rotate = -15;
        }
        else
        {
            rotate = 15;
        }

        if (flip)
        {
            rotate = -1 * rotate;
        }

        _sprite.SetPosition(newPos);
    }

    if (abs(angle - rotate) > 0.5f)
    {
        if (rotate < angle)
        {
            angle = angle - (32 * _deltaTime);
        }
        else
        {
            angle = angle + (32 * _deltaTime);
        }
    }

    _sprite.SetAngle(angle);
}

ltex_t* LoadTexture(const char* _fileName)
{
    int* x = new int;
    int* y = new int;

    unsigned char* buffer = stbi_load(_fileName, x, y, nullptr, 4);
    ltex_t* tex_ = ltex_alloc(*x, *y, 1);

    ltex_setpixels(tex_, buffer);
    stbi_image_free(buffer);

    return tex_;
}

float Clamp(float _value, float _min, float _max)
{
    if (_value < _min)
    {
        return _min;
    }

    if (_value > _max)
    {
        return _max;
    }

    return _value;
}
#pragma endregion