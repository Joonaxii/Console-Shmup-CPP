#include "Entity.h"

Entity::Entity() :Entity("Entity #" + std::to_string(Object::getCurrentID()), false) {}
Entity::Entity(const std::string name, const bool hasCollider) : Object(name), _time(0){
	_engine = Engine::getInstance();

	_collider = hasCollider ? new Collider2D(this, _transform) : nullptr;

	_renderer = new SpriteRenderer();
	_renderer->setTransform(_transform);
	_renderer->setActive(true);
}

Entity::~Entity() {
	Object::~Object();
	delete _renderer;
	delete _collider;
}

SpriteRenderer* Entity::getRenderer() const {
	return _renderer;
}

Collider2D* Entity::getCollider() const {
	return _collider;
}

bool Entity::update(const float deltaTime) {
	if (Object::update(deltaTime)) {
		_time += deltaTime;
		return true;
	}
	return false;
}

