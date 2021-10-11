#define _USE_MATH_DEFINES
#define _WIN32_WINNT 0x0500

#include "Includes.h"
#include "windows.h"
#include "fcntl.h"
#include "io.h"
#include "stdio.h"
#include <sstream>
#include <iostream>
#include "math.h"

Rendering::Rendering() :_buffer { 0 }, _depthBuffer { 0 }, _bufferStream(), _infoClearRegions(), _layerToIndex(), _batch(), _renderers() {

    for (size_t i = 0; i < 4; i++)
    {
        _layerToIndex.insert(std::pair<std::string, int>(layers[i], i));
    }
}

Rendering::~Rendering() { }

const int Rendering::layerNameToIndex(const std::string name) const {

    auto var = _layerToIndex.find(name);
    if (var == _layerToIndex.end()) { return 0; }
    return _layerToIndex.at(name);
}

const std::string Rendering::indexToLayerName(const int index) const {

    if (index < 0 || index >= _layerToIndex.size()) { return std::string(); }
    return layers[index];
}

void Rendering::registerRenderer(SpriteRenderer* renderer) {
    _renderers.push_back(renderer);
}

void Rendering::setup()
{
    std::ios::sync_with_stdio(false);
    std::wios::sync_with_stdio(false);

    HWND consoleWindow = GetConsoleWindow();
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

    _setmode(_fileno(stdout), _O_TEXT);
    setScreenSize(OFFSET_X, OFFSET_Y, RES_X, RES_Y, CHAR_W, CHAR_H);
    memset(_buffer, ' ', CHAR_W * CHAR_H);
}

void Rendering::clearInfoRegion() {

    for (size_t y = 0; y < INFO_H; y++)
    {
        const int hEdge = y == 0 ? -1 : y == INFO_H - 1 ? 1 : 0;
        for (size_t x = 0; x < CHAR_W; x++)
        {
            const int i = INFO_START +  y * CHAR_W + x;
            const int vEdge = x == 0 ? -1 : x == CHAR_W - 1 ? 1 : 0;

            switch (vEdge)
            {
            default:
                _buffer[i] = hEdge == 1 ? '-'  : ' ';
                break;
            case 1:
                switch (hEdge)
                {
                default:
                    _buffer[i] = '|';
                    break;
                case 1:
                    _buffer[i] = '/';
                    break;
                case -1:
                    _buffer[i] = '|';
                    break;
                }
                break;

            case -1:
                switch (hEdge)
                {
                default:
                    _buffer[i] = '|';
                    break;
                case 1:
                    _buffer[i] = '\\';
                    break;
                case -1:
                    _buffer[i] = '|';
                    break;
                }
                break;
            }
        }
    }
}

void Rendering::addInfoString(const int x, const int y, const char* str) {

    const int start = (y) * (CHAR_W) + (x + 1) + INFO_START;
    const int len = strlen(str);

    for (size_t i = 0; i < len; i++)
    {
        const int j = start + i;
        _buffer[j] = str[i];
    }
}

void Rendering::setTitle(const char* str) {

    const int len = strlen(str);
    const int l = len % 2 == 0 ? len : len + 1;

    if (l > CHAR_W) { return; }

    for (size_t y = 0; y < TITLE_H; y++)
    {
        const int hEdge = y == 0 ? -1 : y == TITLE_H - 1 ? 1 : 0;
        for (size_t x = 0; x < CHAR_W; x++)
        {
            const int i = y * CHAR_W + x;
            const int vEdge = x == 0 ? -1 : x == CHAR_W - 1 ? 1 : 0;

            if (vEdge == 0 && hEdge == 0) {

                _buffer[i] = ' ';
                continue;
            }

            switch (vEdge)
            {
            default:
                _buffer[i] = L'-';
                break;
            case 1:
                switch (hEdge)
                {
                default:
                    _buffer[i] = '|';
                    break;
                case 1:
                    _buffer[i] = '|';
                    break;
                case -1:
                    _buffer[i] = '\\';
                    break;
                }
                break;

            case -1:
                switch (hEdge)
                {
                default:
                    _buffer[i] = '|';
                    break;
                case 1:
                    _buffer[i] = '|';
                    break;
                case -1:
                    _buffer[i] = '/';
                    break;
                }
                break;
            }
        }
    }

    const int offset = CHAR_W + CHAR_W / 2 - (l / 2);
    for (size_t i = 0; i < len; i++)
    {
        const int ind = offset + i;
        _buffer[ind] = str[i];
    }
}

void Rendering::render(const float time) {

    //Clear Buffers, the char buffer with the "space" char and depth buffer with 0s 
    memset(&_buffer[GAME_AREA_START], ' ', (CHAR_W * CHAR_H) - GAME_AREA_START);
    memset(&_depthBuffer[GAME_AREA_START], 0, (CHAR_W * CHAR_H) - GAME_AREA_START);
    //clearInfoRegion();

    for (size_t i = 0; i < _renderers.size(); i++)
    {
        const auto rend = _renderers[i];
        if (rend->canRender()) {
            _batch.push(rend);
            continue;
        }
    }

    //TODO: Add sprite rendering etc...
    while (!_batch.empty()) {

        SpriteRenderer* rend = _batch.top();
        _batch.pop();
        renderSprite(rend);
    }

    //Move cursor to top left
    gotoxy(0, 0);

    //Write the buffer to the console
    std::cout.write(_buffer, (CHAR_W * CHAR_H));
    std::cout.flush();
}

void Rendering::renderSprite(SpriteRenderer* renderer) {

    const Sprite* sprt = renderer->getSprite();

    const auto reso = sprt->resolution;
    const auto pos = renderer->positionGrid;

    const unsigned int order = renderer->layer.getUnion();

    for (size_t y = 0; y < reso.y; y++)
    {
        signed int yP = pos.y + y;

        if (yP < 0 || yP >= GAME_AREA_H) { continue; }

        yP += GAME_AREA_Y;
        for (size_t x = 0; x < reso.x; x++)
        {
            signed int xP = pos.x + x;

            if (xP < 0 || xP >= CHAR_W) { continue; }

            const signed int i = yP * CHAR_W + xP;
            const int iP = y * reso.x + x;

            if (_depthBuffer[i] > order) { continue; }

            const char c = sprt->pixels[iP];
            if (c == '½') { continue; }

            _buffer[i] = c;
            _depthBuffer[i] = order;
        }
    }
}

void Rendering::gotoxy(short x, short y) {

    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = { x, y };

    SetConsoleCursorPosition(hStdout, position);
}

void Rendering::setScreenSize(const int x, const int y, const int w, const int h, const int cW, const int cH) {
    HANDLE hConsoleOutput;
    COORD coord;
    CONSOLE_SCREEN_BUFFER_INFO  ConsoleInfo;
    HWND console = GetConsoleWindow();

    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOutput, &ConsoleInfo);
    coord.X = cW;
    coord.Y = cH;

    SetConsoleScreenBufferSize(hConsoleOutput, coord);

    MoveWindow(console, x, y, w, h, TRUE);
}