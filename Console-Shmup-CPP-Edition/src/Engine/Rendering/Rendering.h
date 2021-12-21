#pragma once
#include "SpriteRenderer.h"
#include "Sprite.h"
#include "SortingLayer.h"
#include "../Math/Rect.h"
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>
#include <bitset>

static const std::string layers[7] { "Default", "Background", "EnemiesBG", "Foreground", "EnemiesFG", "UI", "Debug"};

class SpriteRenderer;
class Transform;
class Rendering
{
    static const int SCREEN_W = 960;
    static const int SCREEN_H = 960;

    static const int RES_X = SCREEN_W + 18;
    static const int RES_Y = SCREEN_H + 48;

    static const int OFFSET_X = (RES_X / 2);
    static const int OFFSET_Y = (RES_Y / 2);

public:
    static Transform* MAIN_CAMERA;

    static const int CHAR_W = (int)(SCREEN_W / 8);
    static const int CHAR_H = (int)(SCREEN_H / 8);

    static const int TITLE_START = 0;
    static const int TITLE_H = 3;
    static const int TITLE_END = TITLE_H * CHAR_W;

    static const int INFO_START = TITLE_END;
    static const int INFO_H = 12;
    static const int INFO_END = INFO_START + CHAR_W * INFO_H;

    static const int GAME_AREA_Y = TITLE_H + INFO_H;
    static const int GAME_AREA_START = INFO_END;
    static const int GAME_AREA_H = CHAR_H - (TITLE_H + INFO_H);
    static const int GAME_AREA_END = GAME_AREA_START + GAME_AREA_H * CHAR_W;

    static const Rect GAME_AREA_BOUNDS;

    Rendering();
    ~Rendering();

    void setup();
    void render();

    void toggleCursor(const bool value) const;

    void clearInfoRegion();
    void setTitle(const char* str);

    void addInfoString(const int x, const int y, const char* str);

    const int layerNameToIndex(const std::string name) const;
    const std::string indexToLayerName(const int index) const;

    void registerRenderer(SpriteRenderer* renderer); 

    static void drawSprite(Sprite* sprite, const Vector2& pos, const std::string layerName, const signed short order);

private:

    std::unordered_map<std::string, int> _layerToIndex;

    char _buffer[CHAR_W * CHAR_H];
    unsigned int _depthBuffer[CHAR_W * CHAR_H];
    std::bitset<CHAR_W * INFO_H> _reserved;
   // std::queue<TextRegion> _;

    std::vector<SpriteRenderer*> _renderers;
    std::priority_queue<SpriteRenderer*, std::vector<SpriteRenderer*>, std::greater<SpriteRenderer*>> _batch;

    void setScreenSize(const int x, const int y, const int w, const int h, const int cW, const int cH);
    void gotoxy(short x, short y);

    void renderSprite(SpriteRenderer* renderer);
};

