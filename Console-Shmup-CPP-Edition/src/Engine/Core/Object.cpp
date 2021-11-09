#include "Object.h"

unsigned int Object::_CURRENT_ID = 0;

Object::Object() : Object("New Object") { }
Object::Object(const std::string name) : _position(0, 0), _name(name), _isActive(false), _itClock(0), _ID(_CURRENT_ID++) { }
Object::~Object() { }

#pragma region Get Methods
const bool Object::getIsActive() const {
    return _isActive;
}

const unsigned int Object::getID() const {
    return _ID;
}

const std::string Object::getName() const {
    return _name;
}

const Vector2 Object::getPosition() const {
    return _position;
}
#pragma endregion

void Object::setPosition(const Vector2& position) {
    _position.set(position);
}

void Object::spawn() {
    _isActive = true;
}

void Object::resetClock() {
    _itClock = 0;
}

void Object::moveClock(const float deltaTime) {
    _itClock += deltaTime;
}