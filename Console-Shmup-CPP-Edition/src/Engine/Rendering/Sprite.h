#pragma once
#include "../Math/Rect.h"
#include "../Math/Vector2.h"
#include "../Math/Vector2Int.h"

class Transform;
class Sprite
{
public:
    Sprite();
    Sprite(const char* pix, const Vector2Int& reso, const Vector2& pivot, const char flip);
    ~Sprite();

    const Rect getBounds(const bool flipX, const bool flipY) const;

    void draw(Transform* tr, char* buffer, unsigned int* depthBuffer, const unsigned int depth, const int bufferW, const int bufferH, const int yOffset, const bool flipX, const bool flipY);
    void draw(const Vector2& pos, char* buffer, unsigned int* depthBuffer, const unsigned int depth, const int bufferW, const int bufferH, const int yOffset, const bool flipX, const bool flipY);

private:

    const Vector2Int _resolution;
    const Vector2Int _resMin;

    char** _pixels;

    Vector2* _pivot;
    Rect _bounds;
    Vector2* _offsets;

    char* getFlipSprite(const bool flipX, const bool flipY) const;
    const char flipChar(const char c, const bool flipX, const bool flipY) const;
};

