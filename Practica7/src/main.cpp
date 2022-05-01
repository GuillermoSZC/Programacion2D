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
#define WINDOW_SIZE  Vec2(1000.f, 1000.f)

#pragma region INIT_AUX_FUNCTIONS
void BeeBehavior(Sprite& _spriteref, float _deltatime);
ltex_t* LoadTexture(const char* filename);
float Clamp(float _value, float _min, float _max);
void InputManager(Sprite& _spriteref, float _deltatime);
struct PlayerStates
{
    PlayerStates(GLFWwindow* _window, World* _world, ltex_t* _state1, ltex_t* _state2) : jump(false)
    {
        window = _window;
        world = _world;
        state1 = _state1;
        state2 = _state2;
    }

    GLFWwindow* window;
    World* world;
    ltex_t* state1;
    ltex_t* state2;
    bool jump;
    Vec2 speed = Vec2(0, 0);
};
#pragma endregion

Vec2 cursorPosition = Vec2(0.f, 0.f);

int main() 
{
#pragma region VAR_DECLARATIONS
    double mouseX, mouseY;
    double deltaTime = 0, lastTime = 0, currentTime = glfwGetTime();
    Vec2 cameraPosition = Vec2(0.f, 0.f);
    float camera = 0.f;
#pragma endregion
#pragma region INIT_GLFW_&_VARIABLES
    if (!glfwInit())
    {
        printf("Error to init GLFW.\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow((int)WINDOW_SIZE.x, (int)WINDOW_SIZE.y, "P7", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    lgfx_setup2d((int)WINDOW_SIZE.x, (int)WINDOW_SIZE.y);

    ltex_t* clouds = LoadTexture("data/clouds.png");

    auto* world = new World(0.7f, 0.1f, 0.f, clouds);
    world->SetScrollRatio(0, 2.f);
    world->SetScrollSpeed(0, Vec2(-80.f, -40.f));
    world->SetWindowSize(WINDOW_SIZE);
    world->LoadMap("data/map.tmx", 0);

    ltex_t* idleTexture = LoadTexture("data/idle.png");
    ltex_t* runTexture = LoadTexture("data/run.png");
    auto player = new Sprite(idleTexture, 1, 1);
    player->SetScale(Vec2(1.f, 1.f));
    player->SetBlend(BLEND_ALPHA);
    player->SetPosition(Vec2(120.f, 950.f));
    player->SetCollisionType(Sprite::COLLISION_RECT);

    //|``````````````````````````````````````````````````````````````````````````````````````|
    //| @ CONTROLES:                                                                         |
    //| Para mover el personaje se usa A y D para izquierda o derecha y espacio para saltar. |
    //|                                                                                      |
    //|,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,|

    player->SetCallback(&InputManager);

    PlayerStates playerStates(window, world, idleTexture, runTexture);
    player->SetUserData(&playerStates);

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
            player->Update(FIXED_TICK_60);
        }

        world->Draw(WINDOW_SIZE);
        player->Draw();

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

void InputManager(Sprite& _sprite, float _deltaTime)
{
    auto* playerStates = reinterpret_cast<PlayerStates*>(_sprite.GetUserData());
    Vec2 speed = Vec2(0, 14.f * _deltaTime + playerStates->speed.y);

    if (glfwGetKey(playerStates->window, GLFW_KEY_SPACE) && !playerStates->jump)
    {
        speed = speed + Vec2(0, -6);
        playerStates->jump = true;
    }

    if (glfwGetKey(playerStates->window, GLFW_KEY_A))
    {
        speed.x = (playerStates->jump) ? speed.x - (300 * _deltaTime) : speed.x - (320 * _deltaTime);

        _sprite.SetXFlip(true);
    }

    if (glfwGetKey(playerStates->window, GLFW_KEY_D))
    {
        speed.x = (playerStates->jump) ? speed.x + (300 * _deltaTime) : speed.x + (320 * _deltaTime);

        _sprite.SetXFlip(false);
    }

    if (playerStates->world->MoveSprite(_sprite, speed))
    {
        speed.y = 0;
        playerStates->jump = false;
    }

    if (speed.x != 0.f)
    {
        _sprite.SetTexture(playerStates->state2, 6, 1);
        _sprite.SetFPS(12);
    }
    else
    {
        _sprite.SetTexture(playerStates->state1, 1, 1);
        _sprite.SetFPS(1);
    }
    playerStates->speed = speed;
    _sprite.SetUserData(playerStates);

}
#pragma endregion