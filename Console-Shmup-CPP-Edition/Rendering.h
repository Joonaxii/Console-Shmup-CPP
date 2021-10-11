#pragma once
#include <queue>
#include <vector>
#include <string>
#include <map>
#include <sstream>

static const std::string layers[4] { "Default", "Background" "Foreground", "UI" };

class SpriteRenderer;
class Rendering
{
    static const int SCREEN_W = 1920;
    static const int SCREEN_H = 1080;

    static const int RES_X = (int)(SCREEN_W / 2) + 4;
    static const int RES_Y = (int)(SCREEN_H / 2) + 32;

    static const int OFFSET_X = (SCREEN_W / 2) - (RES_X / 2);
    static const int OFFSET_Y = (SCREEN_H / 2) - (RES_Y / 2);

    static const int CHAR_W = 116;
    static const int CHAR_H = 32;

public:

    static const int TITLE_START = 0;
    static const int TITLE_H = 3;
    static const int TITLE_END = TITLE_H * CHAR_W;

    static const int INFO_START = TITLE_END;
    static const int INFO_H = 5;
    static const int INFO_END = INFO_START + CHAR_W * INFO_H;

    static const int GAME_AREA_START = INFO_END;
    static const int GAME_AREA_H = CHAR_H - (TITLE_H + INFO_H);
    static const int GAME_AREA_END = GAME_AREA_START + GAME_AREA_H * CHAR_W;

    Rendering();
    ~Rendering();

    void setup();
    void render(const float time);

    void clearInfoRegion();
    void setTitle(const char* str);

    void addInfoString(const int x, const int y, const char* str);

    const int layerNameToIndex(const std::string name) const;
    const std::string indexToLayerName(const int index) const;

    void registerRenderer(const SpriteRenderer* renderer);


private:

    class RendererComparer {
    public:
        bool operator() (const SpriteRenderer* a, const SpriteRenderer* b) {

            return (a->layer > b->layer);
        }
    };

    std::map<std::string, int> _layerToIndex;

    char _buffer[CHAR_W * CHAR_H];
    unsigned short _depthBuffer[CHAR_W * CHAR_H];
    std::queue<Vector2Int> _infoClearRegions;

    std::vector<SpriteRenderer*> _renderers;
    std::priority_queue<SpriteRenderer*, std::vector<SpriteRenderer*>, RendererComparer> _batch;
    std::wstreambuf* _bufferStream;

    void setScreenSize(const int x, const int y, const int w, const int h, const int cW, const int cH);
    void gotoxy(short x, short y);
};

