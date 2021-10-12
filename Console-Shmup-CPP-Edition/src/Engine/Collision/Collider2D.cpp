#include "CollisionSystem.h"
#include "Collider2D.h"

bool Collider2D::collidesWith(const Collider2D& other) {

	switch (_type) {

	case ColliderType::POINT:
		switch (other._type) {
		case ColliderType::POINT:
			return CollisionSystem::pointVsPoint(_position, other._position);
		case ColliderType::CIRCLE:
			return CollisionSystem::pointVsCircle(_position, other._position, other._radSqrd);
		case ColliderType::BOX:
			return CollisionSystem::pointVsAABB(_position, other._min, other._max);
		}
		break;

	case ColliderType::CIRCLE:
		switch (other._type) {
		case ColliderType::POINT:
			return CollisionSystem::pointVsCircle(other._position, _position, _radSqrd);
		case ColliderType::CIRCLE:
			return CollisionSystem::cicrleVsCircle(_position, _size.y, other._position, other._size.y);
		case ColliderType::BOX:
			return CollisionSystem::aabbVsCircle(other._min, other._max, _position, _radSqrd);
		}
		break;

	case ColliderType::BOX:
		switch (other._type) {
		case ColliderType::POINT:
			return CollisionSystem::pointVsAABB(other._position, _min, _max);
		case ColliderType::CIRCLE:
			return CollisionSystem::aabbVsCircle(_min, _max, other._position, other._radSqrd);
		case ColliderType::BOX:
			return CollisionSystem::aabbVsAABB(_min, _max, other._min, other._max);
		}
		break;
	}
	return false;
}
