#pragma once
#include "../../Includes.h"
#include "../Math/Rect.h"
#include "../Math/Vector2.h"

class Vector2Int;
class Sprite
{
public:
    Sprite();
    Sprite(const char* pix, Vector2Int reso, Vector2 _pivot);
    ~Sprite();

    const Rect getBounds() const;

    void draw(Transform* tr, char* buffer, unsigned int* depthBuffer, const unsigned int depth, const int bufferW, const int bufferH, const int yOffset, const bool flipX, const bool flipY);
    void draw(const Vector2& pos, char* buffer, unsigned int* depthBuffer, const unsigned int depth, const int bufferW, const int bufferH, const int yOffset, const bool flipX, const bool flipY);

private:
    const Vector2 _pivot;
    const Vector2Int _resolution;
    char* _pixels;

    Rect _bounds;
};

