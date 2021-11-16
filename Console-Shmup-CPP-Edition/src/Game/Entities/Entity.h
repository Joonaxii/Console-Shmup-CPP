#pragma once
#include "../../Engine/Collision/Collider2D.h"
#include "../../Engine/Core/Object.h"
#include "../../Engine/Core/Vector2.h"
#include "../../Includes.h"

class Entity : public Object
{
public:
    Entity();
    Entity(const int maxHP);
    Entity(std::string name, const int maxHP);
    ~Entity();

    virtual bool takeDamage(const int damage, Object* damageDealer);
    virtual void kill(bool silent, Object* killer);
    virtual bool update(const float deltaTime);

    void setMaxHP(const int newHP, const bool setCurrent = false);

protected:

    bool _isDead;

    SpriteRenderer _renderer;
    Collider2D _collider;

    int _curentHP;
    int _maxHP;

    virtual void onCollisionEnter(Collider2D& other) = 0;
    virtual void onCollisionStay(Collider2D& other) = 0;
    virtual void onCollisionExit(Collider2D& other) = 0;
};

