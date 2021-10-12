#pragma once
#include "Includes.h"
#include "string"

class Vector2;
class Sprite;
class SpriteRenderer
{
public:
    SpriteRenderer();
    ~SpriteRenderer();

    Vector2Int positionGrid;
    SortingLayer layer;

    void setLayer(const std::string name);
    void setSortingOrder(const unsigned short order);
    void setPosition(const Vector2& position);    

    const Vector2 getPosition() const;

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
    Vector2 _position;
};

