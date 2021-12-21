#include "CollisionSystem.h"
#include "../Math/Math.h"
#include "../Engine.h"

CollisionSystem::CollisionSystem() : _colliderCount(0), _colliders(0)  { 
}
CollisionSystem::~CollisionSystem() { }

unsigned int CollisionSystem::registerCollider(Collider2D* collider) {
	auto inst = Engine::getInstance()->getCollisionSystem();
	inst->_colliders.push_back(collider);
	return inst->_colliderCount++;
}

const bool CollisionSystem::pointVsAABB(const Vector2& pointA, const Vector2& minB, const Vector2& maxB) {
	return !(minB.x > pointA.x || minB.y > pointA.y || maxB.x < pointA.x || maxB.y < pointA.y);
}

const bool CollisionSystem::pointVsCircle(const Vector2& pointA, const Vector2& pointB, const float radSqrdB) {
	const float dX = pointA.x - pointB.x;
	const float dY = pointA.y - pointB.y;

	return dX * dX + dY * dY <= radSqrdB;
}

const bool CollisionSystem::pointVsPoint(const Vector2& pointA, const Vector2& pointB) {
	return &pointA == &pointB;
}

const bool CollisionSystem::aabbVsAABB(const Vector2& minA, const Vector2& maxA, const Vector2& minB, const Vector2& maxB) {
	return !(minA.x > maxB.x || minA.y > maxB.y || maxA.x < minB.x || maxA.y < minB.y);
}

const bool CollisionSystem::aabbVsCircle(const Vector2& minA, const Vector2& maxA, const Vector2& pointB, const float radSqrdB) {

	const float dX = pointB.x - clamp(pointB.x, minA.x, maxA.x);
	const float dY = pointB.y - clamp(pointB.y, minA.y, maxA.y);

	return dX * dX + dY * dY <= radSqrdB;
}

const bool CollisionSystem::cicrleVsCircle(const Vector2& pointA, const float radA, const Vector2& pointB, const float radB) {

	const float radSqrd = radA + radB;

	const float dX = pointA.x - pointB.x;
	const float dY = pointA.y - pointB.y;

	return dX * dX + dY * dY <= radSqrd * radSqrd;
}

const unsigned int CollisionSystem::getColliderCount() const {
	return _colliderCount;
}

const Collider2D* CollisionSystem::getCollider(const unsigned int id) {
	return id >= _colliders.size() ? nullptr : _colliders[id];
}

void CollisionSystem::update() {
	for (size_t i = 0; i < _colliders.size(); i++) {
		auto cA = _colliders[i];
		cA->clear();
		cA->update();
	}
}
