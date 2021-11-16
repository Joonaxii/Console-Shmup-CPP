#pragma once
#include "../../Includes.h"

class Vector2Int;
class Sprite
{
public:
    const Vector2 pivot;
    const Vector2Int resolution;
    char* pixels;

    Sprite();
    Sprite(const char* pix, Vector2Int reso, Vector2 pivot);
    ~Sprite();

    void draw(Transform* tr, char* buffer, unsigned int* depthBuffer, const unsigned int depth, const int bufferW, const int bufferH, const int yOffset, const bool flipX, const bool flipY);
};

