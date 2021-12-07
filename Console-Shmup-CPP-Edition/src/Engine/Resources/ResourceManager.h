#pragma once
#include "../../Includes.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <locale>
#include "../Rendering/Animation.h"

class Sprite;
class ResourceManager
{

public:
    ResourceManager();
    ~ResourceManager();

    bool tryGetSprite(const std::string name, Sprite** spriteOut);
    bool tryGetAnimation(const std::string name, Animation** animOut);

private:

    static const std::string SPRITE_PATH;
    static const std::locale LOCALE;
    std::unordered_map<std::string, Sprite*, std::hash<std::string>> _sprites;
    std::unordered_map<std::string, Animation*, std::hash<std::string>> _animations;

    void loadSprites();
    void loadAnimations();

    int tryLoadSprite(const std::string path, Sprite** sprite, const std::locale locale);
    int tryLoadAnimFrame(std::wifstream& stream, Sprite** sprite);

    char replacementChars(const char input);
    char convertToANSI(const wchar_t input);

};


