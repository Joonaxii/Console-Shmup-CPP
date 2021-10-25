#include "CollisionSystem.h"
#include "../Core/Math.h"

CollisionSystem::CollisionSystem() : _colliderCount(0), _colliders() { }
CollisionSystem::~CollisionSystem() { }

unsigned int CollisionSystem::registerCollider(Collider2D* collider) {
	_colliders.push_back(collider);
	return _colliderCount++;
}

const bool CollisionSystem::pointVsAABB(const Vector2& pointA, const Vector2& minB, const Vector2& maxB) {
	return !(minB.x > pointA.x || minB.y > pointA.y || maxB.x < pointA.x || maxB.y < pointA.y);
}

const bool CollisionSystem::pointVsCircle(const Vector2& pointA, const Vector2& pointB, const float& radSqrdB) {

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

const bool CollisionSystem::aabbVsCircle(const Vector2& minA, const Vector2& maxA, const Vector2& pointB, const float& radSqrdB) {

	const float dX = pointB.x - clamp(pointB.x, minA.x, maxA.x);
	const float dY = pointB.y - clamp(pointB.y, minA.y, maxA.y);

	return dX * dX + dY * dY <= radSqrdB;
}

const bool CollisionSystem::cicrleVsCircle(const Vector2& pointA, const float& radA, const Vector2& pointB, const float& radB) {

	const float radSqrd = radA + radB;

	const float dX = pointA.x - pointB.x;
	const float dY = pointA.y - pointB.y;

	return dX * dX + dY * dY <= radSqrd * radSqrd;
}
