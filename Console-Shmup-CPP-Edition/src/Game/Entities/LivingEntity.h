#pragma once
#include "Entity.h"

class LivingEntity : public Entity {

public:

    LivingEntity();
    ~LivingEntity();

    virtual void kill(bool silent, Object* killer);
    virtual bool takeDamage(const int damage, Object* damageDealer);
    void setMaxHP(const int newHP, const bool setCurrent = false);

protected:

    bool _isDead;
    int _curentHP;
    int _maxHP;

    virtual void onCollisionEnter(Collider2D& other) = 0;
    virtual void onCollisionStay(Collider2D& other) = 0;
    virtual void onCollisionExit(Collider2D& other) = 0;
};

