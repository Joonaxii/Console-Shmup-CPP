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
    void setPosition(const Vector2& position);
    const bool canRender() const;

private:

    bool _isActive;
    Rendering* _rendering;
    Sprite* _sprite;
    Vector2 _position;
};

