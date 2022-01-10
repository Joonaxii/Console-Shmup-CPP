#pragma once
#include "../../Engine/Collision/Collider2D.h"
#include "../../Engine/Core/Object.h"
#include "../../Engine/Math/Vector2.h"
#include "../../Includes.h"

class Entity : public Object
{
public:
    Entity();
    Entity(const std::string name, const bool hasCollider);
    virtual ~Entity();

    SpriteRenderer* getRenderer() const;
    Collider2D* getCollider() const;

    virtual bool update(const float deltaTime);

protected:

    Engine* _engine;

    SpriteRenderer* _renderer;
    Collider2D* _collider;

    float _time;

    virtual void onCollisionEnter(Collider2D& other) = 0;
    virtual void onCollisionStay(Collider2D& other) = 0;
    virtual void onCollisionExit(Collider2D& other) = 0;
};

