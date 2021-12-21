#pragma once
#include "../Math/Vector2.h"
#include "ObjectPool.h"
#include "../Components/Transform.h"

class Vector2;
class ObjectPool;
class Transform;
class Object
{
   
public:

    Object();
    Object(const std::string name);
    Object(const std::string name, ObjectPool* pool);
    virtual ~Object();

    static const unsigned int getCurrentID();

    const unsigned int getID() const;

    Transform* getTransform() const;

    const bool getIsActive() const;
    const std::string getName() const;

    virtual void spawn();
    virtual void spawn(const Vector2& position);

    virtual void deSpawn();
    virtual bool update(const float deltaTime);

protected:

    std::string _name;
    bool _isActive;

    float _itClock;
    ObjectPool* _pool;
    Transform* _transform;

    const unsigned int _ID;

    virtual void applyPosition();
    void resetClock();
    void moveClock(const float deltaTime);

private:
    static unsigned int _CURRENT_ID;
};

