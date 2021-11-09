#pragma once
#include "../../Includes.h"

class Entity : public Object
{

public:
    Entity();
    ~Entity();

protected:

    virtual void onCollisionEnter(Collider2D& other) = 0;
    virtual void onCollisionStay(Collider2D& other) = 0;
    virtual void onCollisionExit(Collider2D& other) = 0;
};

