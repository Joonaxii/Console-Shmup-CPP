#pragma once
#include "../../Engine/Collision/Collider2D.h"
#include "../../Engine/Core/Object.h"
#include "../../Engine/Math/Vector2.h"
#include "../../Includes.h"

class Entity : public Object
{
public:
    Entity();
    Entity(const std::string name);
    ~Entity();

    Transform* getTransform() const;

    virtual bool update(const float deltaTime);
    virtual void setPosition(const Vector2& position);

protected:

    Transform* _transform;
    SpriteRenderer* _renderer;
    Collider2D* _collider;

    virtual void onCollisionEnter(Collider2D& other) = 0;
    virtual void onCollisionStay(Collider2D& other) = 0;
    virtual void onCollisionExit(Collider2D& other) = 0;
};

