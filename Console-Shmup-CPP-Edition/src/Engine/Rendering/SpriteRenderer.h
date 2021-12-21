#pragma once
#include "../Math/Rect.h"
#include "string"
#include "SortingLayer.h"
#include "../Components/Transform.h"
#include "../Components/TransformConstraints.h"

class Rendering;
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
    void setSortingOrder(const signed short order);
    void draw(char* buffer, unsigned int* depthBuffer);

    void setFlipX(const bool val);
    void setFlipY(const bool val);

    const bool getFlipX() const;
    const bool getFlipY() const;

    const Rect getBounds() const;

    const Sprite* getSprite() const;

    const bool canRender() const;

    void setActive(const bool active);
    void setSprite(Sprite* sprite);

    const bool operator<(const SpriteRenderer& other) const;
    const bool operator>(const SpriteRenderer& other) const;

private:

    SortingLayer _debugLayer;

    bool _flipX;
    bool _flipY;

    bool _isActive;
    Rendering* _rendering;

    Sprite* _sprite;
    Sprite* _boundSprite;

    Transform* _transform;

    TransformConstraints _constraints;

    Rect _bounds;
};

