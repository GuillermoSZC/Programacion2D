#include "World.h"
#include "pugixml.cpp"
#include "stb_image.h"
#include <iostream>



World::World(float _clearRed, float _clearGreen, float _clearBlue,
    const ltex_t* _background) :
    clearRed(_clearRed), clearBlue(_clearBlue), clearGreen(_clearGreen)
{
    background.texture = _background;
}

#pragma region FUNCTIONS
void World::Update(float _deltaTime)
{
    background.scrollOffset.x = background.scrollOffset.x + background.scrollSpeed.x * _deltaTime;
    background.scrollOffset.y = background.scrollOffset.y + background.scrollSpeed.y * _deltaTime;
    background.scroll.x = (cameraPosition.x * background.scrollRatio + background.scrollOffset.x) / background.texture->width;
    background.scroll.y = (cameraPosition.y * background.scrollRatio + background.scrollOffset.y) / background.texture->height;

    for (Sprite* sprite : spritesList)
    {
        sprite->Update(_deltaTime);
    }
}

void World::Draw(const Vec2& _screenSize)
{
    lgfx_clearcolorbuffer(clearRed, clearGreen, clearBlue);
    lgfx_setorigin(cameraPosition.x, cameraPosition.y);
    lgfx_setblend(BLEND_ALPHA);

    float u1 = background.scroll.x + _screenSize.x / background.texture->width;
    float v1 = background.scroll.y + _screenSize.y / background.texture->height;
    ltex_drawrotsized(background.texture, cameraPosition.x, cameraPosition.y, 0.f, 0.f, 0.f, _screenSize.x, _screenSize.y,
        background.scroll.x, background.scroll.y, u1, v1);

    for (Sprite* sprite : spritesList)
    {
        sprite->Draw();
    }
}

void World::AddSprite(Sprite& _sprite)
{
    spritesList.push_back(&_sprite);
}

void World::RemoveSprite(Sprite& _sprite)
{
    spritesList.remove(&_sprite);
}


inline std::string ExtractPath(const std::string& _fileName) {
    std::string filenameCopy = _fileName;
    while (filenameCopy.find("\\") != std::string::npos) {
        filenameCopy.replace(filenameCopy.find("\\"), 1, "/");
    }
    filenameCopy = filenameCopy.substr(0, filenameCopy.rfind('/'));
    if (filenameCopy.size() > 0) filenameCopy += "/";
    return filenameCopy;
}

ltex_t* WorldLoadTexture(const char* _fileName)
{
    int* x = new int;
    int* y = new int;

    unsigned char* buffer = stbi_load(_fileName, x, y, nullptr, 4);
    ltex_t* tex_ = ltex_alloc(*x, *y, 1);

    ltex_setpixels(tex_, buffer);
    stbi_image_free(buffer);

    return tex_;
}


bool World::LoadMap(const char* _fileName, uint16_t _firstColId)
{
#pragma region VARIABLES
    pugi::xml_document xmlDocument;
    pugi::xml_parse_result parseResult;
    pugi::xml_node xmlNode;
    Vec2 tileSize;
    Vec2 tileFrames;
    std::string texture;
    const ltex_t* tileSet;
    float x, y;
    Vec2 tileScale;
    Vec2 tileOffset;
    int iterator = 0;
    int gid;
    float mapRatio;
#pragma endregion 

    parseResult = xmlDocument.load_file(_fileName);

    if (parseResult)
    {
        xmlNode = xmlDocument.child("map");

        mapSize.x = xmlNode.attribute("width").as_int();
        mapSize.y = xmlNode.attribute("height").as_int();

        tileSize = Vec2(xmlNode.attribute("tilewidth").as_int(), xmlNode.attribute("tileheight").as_int());

        tileFrames.x = xmlNode.child("tileset").attribute("columns").as_int();
        tileFrames.y = xmlNode.child("tileset").attribute("tilecount").as_int() / tileFrames.x;

        texture = ExtractPath(_fileName) + xmlNode.child("tileset").child("image").attribute("source").as_string();

        tileSet = WorldLoadTexture(texture.c_str());

        x = windowSize.x / (mapSize.x * mapSize.y);
        y = windowSize.y / (mapSize.x * mapSize.y);

        tileScale = Vec2(x, y);
        tileOffset = Vec2(tileSize.x * tileScale.x, tileSize.y * tileScale.y);

        for (pugi::xml_node itNode = xmlNode.child("layer").child("data").child("tile"); itNode; itNode = itNode.next_sibling("tile"))
        {
            gid = itNode.attribute("gid").as_int();
            if (gid != 0)
            {
                auto* sprite = new Sprite(tileSet, tileFrames.x, tileFrames.y);

                sprite->SetCurrentFrame(gid - _firstColId);
                sprite->SetScale(tileScale);
                sprite->SetPosition(Vec2((0.5f + iterator % int(mapSize.x)) * tileOffset.x, (0.5f + int(iterator / int(mapSize.x))) * tileOffset.y));
                sprite->SetCollisionType(Sprite::CollisionType::COLLISION_RECT);

                spritesList.push_back(sprite);
            }
            iterator++;
        }

        mapRatio = mapSize.y / mapSize.x;
        mapSize.x = windowSize.x;
        mapSize.y = windowSize.x * mapRatio;

        return true;
    }
    printf(parseResult.description());
    return false;
}

bool World::MoveSprite(Sprite& _sprite, const Vec2& _amount)
{
    bool collides = false;
    Vec2 position;

    position = _sprite.GetPosition();
    _sprite.SetPosition(Vec2(position.x + _amount.x, position.y));

    for (auto sprite : spritesList)
    {
        if (_sprite.Collides(*sprite))
        {
            _sprite.SetPosition(position);
            collides = true;
            break; 
        } 
    }

    _sprite.SetPosition(Vec2(_sprite.GetPosition().x, _sprite.GetPosition().y + _amount.y));

    for (auto sprite : spritesList)
    {
        if (_sprite.Collides(*sprite))
        {
            _sprite.SetPosition(Vec2(_sprite.GetPosition().x, position.y));
            collides = true;
            break; 
        }
    }

    return collides;
}
#pragma endregion

#pragma region GETTERS_AND_SETTERS
float World::GetClearRed() const
{
    return clearRed;
}

float World::GetClearGreen() const
{
    return clearGreen;
}

float World::GetClearBlue() const
{
    return clearBlue;
}

const ltex_t* World::GetBackground(size_t _layer) const
{
    if (_layer >= 0 && _layer < 4)
    {
        return background.texture;
    }
    return nullptr;
}

float World::GetScrollRatio(size_t _layer) const
{
    if (_layer >= 0 && _layer < 4)
    {
        return background.scrollRatio;
    }
    return 0.f;
}

const Vec2& World::GetScrollSpeed(size_t _layer) const
{
    if (_layer >= 0 && _layer < 4)
    {
        return background.scrollSpeed;
    }

    return Vec2(0.f, 0.f);
}

const Vec2& World::GetCameraPosition() const
{
    return cameraPosition;
}

const Vec2& World::GetWindowSize() const
{
    return windowSize;
}

const Vec2& World::GetMapSize() const
{
    return mapSize;
}

void World::SetScrollRatio(size_t _layer, float _ratio)
{
    if (_layer >= 0 && _layer < 4)
    {
        background.scrollRatio = _ratio;
    }
}

void World::SetScrollSpeed(size_t _layer, const Vec2& _speed)
{
    if (_layer >= 0 && _layer < 4)
    {
        background.scrollSpeed = _speed;
    }
}

void World::SetCameraPosition(const Vec2& _position)
{
    cameraPosition = _position;
}

void World::SetWindowSize(Vec2& _windowSize)
{
    windowSize = _windowSize;
}

void World::SetMapSize(Vec2& _mapSize)
{
    mapSize = _mapSize;
}

#pragma endregion