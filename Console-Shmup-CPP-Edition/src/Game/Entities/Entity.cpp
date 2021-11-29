#include "Entity.h"

Entity::Entity() :Entity("Entity #" + std::to_string(Object::getCurrentID())) {}
Entity::Entity(const std::string name) : Object(name) {
	_transform = new Transform();
	_collider = new Collider2D(this, _transform);

	_renderer = new SpriteRenderer();
	_renderer->setTransform(_transform);
}

Entity::~Entity() {
	delete _transform;
	delete _renderer;
	delete _collider;
}

Transform* Entity::getTransform() const {
	return _transform;
}

void Entity::setPosition(const Vector2& position) {
	Object::setPosition(position);

	_collider->setPosition(_position);
	//_renderer.setPosition(_position);
}


bool Entity::update(const float deltaTime) {
	return Object::update(deltaTime);
}

