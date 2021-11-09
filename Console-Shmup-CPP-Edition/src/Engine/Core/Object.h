#pragma once
#include "Vector2.h"

class Vector2;
class Object
{
   
public:

    Object();
    Object(const std::string name);
    ~Object();

    const unsigned int getID() const;

    const bool getIsActive() const;
    const std::string getName() const;

    virtual void setPosition(const Vector2& position);
    const Vector2 getPosition() const;

    virtual void spawn();
    virtual const bool update(const float deltaTime) = 0;

protected:

    std::string _name;
    bool _isActive;

    Vector2 _position;
    float _itClock;

    const unsigned int _ID;

    void resetClock();
    void moveClock(const float deltaTime);

private:
    static unsigned int _CURRENT_ID;
};

