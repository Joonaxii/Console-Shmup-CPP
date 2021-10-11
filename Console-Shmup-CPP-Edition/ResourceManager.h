#pragma once
#include "Includes.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <locale>

class Sprite;
class ResourceManager
{

public:
    ResourceManager();
    ~ResourceManager();

    bool tryGetSprite(const std::string name, Sprite** spriteOut);

private:

    static const std::string SPRITE_PATH;
    std::unordered_map<std::string, Sprite*, std::hash<std::string>> _sprites;

    void loadSprites();
    int tryLoadSprite(const std::string path, Sprite** sprite);

    char convertToANSI(const wchar_t input);

};


