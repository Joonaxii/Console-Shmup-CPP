#include "Object.h"

unsigned int Object::_CURRENT_ID = 0;

Object::Object() : Object("New Object") { }
Object::Object(const std::string name) : _position(0,0), _name(name), _isAlive(false), _itClock(0), _ID(_CURRENT_ID++) { }
Object::~Object(){}


void Object::setPosition(const Vector2& position) {
    _position.set(position);
}