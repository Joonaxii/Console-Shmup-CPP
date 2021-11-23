#pragma once
#include "../../Includes.h"
#include "../Math/Rect.h"
#include "string"
#include "../../../Transform.h"

class Vector2;
class Sprite;
class SpriteRenderer
{
public:
    static bool DRAW_BOUNDS;

    SpriteRenderer();
    ~SpriteRenderer();

    SortingLayer layer;

    void setTransform(Transform* transform);

    void setLayer(const std::string name);
    void setSortingOrder(const unsigned short order);
    void draw(char* buffer, unsigned int* depthBuffer);

    const Rect getBounds() const;

    Sprite* getSprite();

    const bool canRender() const;

    void setActive(const bool active);
    void setSprite(Sprite* sprite);

    const bool operator<(const SpriteRenderer& other) const;
    const bool operator>(const SpriteRenderer& other) const;

private:

    SortingLayer _debugLayer;

    bool _isActive;
    Rendering* _rendering;
    Sprite* _sprite;
    Sprite* _boundSprite;
    Transform* _transform;

    Rect _bounds;
};

