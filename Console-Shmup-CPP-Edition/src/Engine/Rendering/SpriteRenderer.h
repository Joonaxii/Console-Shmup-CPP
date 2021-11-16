#pragma once
#include "../../Includes.h"
#include "string"
#include "../../../Transform.h"

class Vector2;
class Sprite;
class SpriteRenderer
{
public:
    SpriteRenderer();
    ~SpriteRenderer();

    SortingLayer layer;

    void setTransform(Transform* transform);

    void setLayer(const std::string name);
    void setSortingOrder(const unsigned short order);
    void draw(char* buffer, unsigned int* depthBuffer);

    Sprite* getSprite();

    const bool canRender() const;

    void setActive(const bool active);
    void setSprite(Sprite* sprite);

    const bool operator<(const SpriteRenderer& other) const;
    const bool operator>(const SpriteRenderer& other) const;

private:

    bool _isActive;
    Rendering* _rendering;
    Sprite* _sprite;
    Transform* _transform;
};

