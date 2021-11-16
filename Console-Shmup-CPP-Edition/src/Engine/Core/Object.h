#pragma once
#include "Vector2.h"
#include "ObjectPool.h"

class Vector2;
class ObjectPool;
class Object
{
   
public:

    Object();
    Object(const std::string name);
    Object(const std::string name, ObjectPool* pool);
    ~Object();

    static const unsigned int getCurrentID();

    const unsigned int getID() const;

    const bool getIsActive() const;
    const std::string getName() const;

    void setPosition(const Vector2& position);
    const Vector2 getPosition() const;

    virtual void spawn();
    virtual void spawn(const Vector2& position);

    virtual void deSpawn();
    virtual bool update(const float deltaTime);

protected:

    std::string _name;
    bool _isActive;

    Vector2 _position;
    float _itClock;

    ObjectPool* _pool;

    const unsigned int _ID;

    virtual void applyPosition();
    void resetClock();
    void moveClock(const float deltaTime);

private:
    static unsigned int _CURRENT_ID;
};

