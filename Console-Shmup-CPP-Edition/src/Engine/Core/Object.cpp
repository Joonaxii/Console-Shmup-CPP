#include "Object.h"
#include "ObjectPool.h"

unsigned int Object::_CURRENT_ID = 0;

Object::Object() : Object("Object #" + std::to_string(_CURRENT_ID)) { }
Object::Object(const std::string name) : Object(name, nullptr) { }
Object::Object(const std::string name, ObjectPool* pool) : _name(name), _isActive(true), _itClock(0), _ID(_CURRENT_ID++), _pool(pool) { 
    _transform = new Transform();
}
Object::~Object() { 
    delete _transform;
}

const unsigned int Object::getCurrentID() { return _CURRENT_ID; }

#pragma region Get Methods
const bool Object::getIsActive() const {
    return _isActive;
}

const unsigned int Object::getID() const {
    return _ID;
}

Transform* Object::getTransform() const {
    return _transform;
}


const std::string Object::getName() const {
    return _name;
}


#pragma endregion

void Object::spawn() {
    resetClock();
    _isActive = true;
}

void Object::spawn(const Vector2& position) {
    _transform->setPosition(position, true);
}

void Object::deSpawn() {
    if (_pool != nullptr) {
        _pool->returnObj(this);
    }
    _isActive = true;
}

bool Object::update(const float deltaTime)
{
    moveClock(deltaTime);
    return _isActive;
}

void Object::applyPosition() { }

void Object::resetClock() {
    _itClock = 0;
}

void Object::moveClock(const float deltaTime) {
    _itClock += deltaTime;
}