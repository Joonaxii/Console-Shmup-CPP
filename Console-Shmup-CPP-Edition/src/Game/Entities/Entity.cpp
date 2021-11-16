#include "Entity.h"

Entity::Entity() : Entity(100) {}
Entity::Entity(const int maxHP) : Entity("Entity #" + std::to_string(Object::getCurrentID()), maxHP) { }
Entity::Entity(std::string name, const int maxHP) : Object(name), _isDead(true), _maxHP(maxHP), _curentHP(0), _renderer(), _collider(this) { }

Entity::~Entity()
{
}

void Entity::setPosition(const Vector2& position) {
	Object::setPosition(position);

	_collider.setPosition(_position);
	//_renderer.setPosition(_position);
}

bool Entity::takeDamage(const int damage, Object* damageDealer) {
	return false;
}

void Entity::kill(bool silent, Object* killer) {
}

bool Entity::update(const float deltaTime) {
	return Object::update(deltaTime);
}

void Entity::setMaxHP(const int newHP, const bool setCurrent) {
	_maxHP = newHP;

	if (!setCurrent) { return; }
	_curentHP = newHP;
}
