#include "Entity.h"

Entity::Entity() :Entity("Entity #" + std::to_string(Object::getCurrentID())) {}
Entity::Entity(const std::string name) : Object(name) {
	_engine = Engine::getInstance();

	_collider = new Collider2D(this, _transform);

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
	return Object::update(deltaTime);
}

