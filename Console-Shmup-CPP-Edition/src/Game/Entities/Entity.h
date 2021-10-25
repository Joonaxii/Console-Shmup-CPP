#pragma once
#include "../../Includes.h"

class Entity : public Object
{
protected:

    virtual void OnCollisionEnter(Collider2D& other);
    virtual void OnCollisionStay(Collider2D& other);
    virtual void OnCollisionExit(Collider2D& other);
};

