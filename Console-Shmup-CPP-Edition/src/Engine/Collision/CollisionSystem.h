#pragma once
#include <vector>
#include "../Core/Vector2.h"

class Collider2D;
class CollisionSystem
{
public:

	CollisionSystem();
	~CollisionSystem();

    unsigned int registerCollider(Collider2D* collider);

	static const bool pointVsAABB(const Vector2& pointA, const Vector2& minB, const Vector2& maxB);
	static const bool pointVsCircle(const Vector2& pointA, const Vector2& pointB, const float radSqrdB);
	static const bool pointVsPoint(const Vector2& pointA, const Vector2& pointB);

	static const bool aabbVsAABB(const Vector2& minA, const Vector2& maxA, const Vector2& minB, const Vector2& maxB);
	static const bool aabbVsCircle(const Vector2& minA, const Vector2& maxA, const Vector2& pointB, const float radSqrdB);

	static const bool cicrleVsCircle(const Vector2& pointA, const float radA, const Vector2& pointB, const float radB);

private:
	unsigned int _colliderCount;
	std::vector<Collider2D*> _colliders;
};

