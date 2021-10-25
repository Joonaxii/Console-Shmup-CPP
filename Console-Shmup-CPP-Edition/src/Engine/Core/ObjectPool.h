#pragma once
#include <queue>
#include <functional>
#include "Object.h"

class ObjectPool
{
public:

    ObjectPool(std::function<Object* (ObjectPool*)> createNew) : ObjectPool(createNew, 64) {}
    ObjectPool(std::function<Object* (ObjectPool*)> createNew, const int capacity);
    ~ObjectPool();

    Object* get();
    void returnObj(Object* obj);

private:
    std::queue<Object*> _pool;
    std::function<Object*(ObjectPool*)> _createNew;

    Object* getNew();
};

