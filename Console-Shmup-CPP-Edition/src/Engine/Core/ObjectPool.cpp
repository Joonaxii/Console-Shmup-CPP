#include "ObjectPool.h"

ObjectPool::ObjectPool(std::function<Object* (ObjectPool*)> createNew, const int initialCount) : _pool() {
    _createNew = createNew;
    for (size_t i = 0; i < initialCount; i++)
    {
        returnObj(getNew());
    }
}

ObjectPool::~ObjectPool() {
    while (!_pool.empty()) {

        auto temp = _pool.back();
        _pool.pop();
        delete temp;
    }
}

Object* ObjectPool::get() {

    if (_pool.empty()) { return getNew(); }

    auto obj = _pool.back();
    _pool.pop();
    return obj;
}

void ObjectPool::returnObj(Object* obj) {
    _pool.push(obj);
}

Object* ObjectPool::getNew() {
    return _createNew(this);
}

