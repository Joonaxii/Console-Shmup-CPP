#include "ColliderData.h"
#include "CollisionSystem.h"

const bool ColliderData::collidesWith(const ColliderData& other) const {
	switch (_type) {
	case ColliderType::POINT:
		switch (other._type) {
		case ColliderType::POINT:
			return CollisionSystem::pointVsPoint(_center, other._center);
		case ColliderType::CIRCLE:
			return CollisionSystem::pointVsCircle(_center, other._center, other._radSqrd);
		case ColliderType::BOX:
			return CollisionSystem::pointVsAABB(_center, other._min, other._max);
		}
		break;

	case ColliderType::CIRCLE:
		switch (other._type) {
		case ColliderType::POINT:
			return CollisionSystem::pointVsCircle(other._center, _center, _radSqrd);
		case ColliderType::CIRCLE:
			return CollisionSystem::cicrleVsCircle(_center, _size.y, other._center, other._size.y);
		case ColliderType::BOX:
			return CollisionSystem::aabbVsCircle(other._min, other._max, _center, _radSqrd);
		}
		break;

	case ColliderType::BOX:
		switch (other._type) {
		case ColliderType::POINT:
			return CollisionSystem::pointVsAABB(other._center, _min, _max);
		case ColliderType::CIRCLE:
			return CollisionSystem::aabbVsCircle(_min, _max, other._center, other._radSqrd);
		case ColliderType::BOX:
			return CollisionSystem::aabbVsAABB(_min, _max, other._min, other._max);
		}
		break;
	}
	return false;
}

ColliderData::ColliderData() : _type(), _size(0, 0), _radSqrd(0), _center(0, 0), _min(0, 0), _max(0, 0), _offset(0, 0) { }

ColliderData::ColliderData(const Vector2 offset) : _type(ColliderType::POINT), _size(0, 0), _radSqrd(0), _center(0, 0), _min(0, 0), _max(0, 0), _offset(offset) { }
ColliderData::ColliderData(const Vector2 offset, const float radius) : _type(ColliderType::CIRCLE), _size(radius, radius), _radSqrd(radius * radius), _center(0, 0), _min(0, 0), _max(0, 0), _offset(offset) { }
ColliderData::ColliderData(const Vector2 offset, const Vector2 size) : _type(ColliderType::POINT), _size(size), _radSqrd(0), _center(0, 0), _min(0, 0), _max(0, 0), _offset(offset) { }

const Vector2 ColliderData::getMin() const { return Vector2(_min); }
const Vector2 ColliderData::getMax() const { return Vector2(_max); }

void ColliderData::copyFrom(const ColliderData& other){

	_type = other._type;

	_size.x = other._size.x;
	_size.y = other._size.y;

	_offset.x = other._offset.x;
	_offset.y = other._offset.y;

	_radSqrd = other._radSqrd;
}

void ColliderData::update(Vector2& center) {
	_center = center + _offset;
	switch (_type)
	{
	case ColliderType::POINT:
		_min.set(_center);
		_max.set(_center);
		break;

	case ColliderType::BOX:
	case ColliderType::CIRCLE:
		_min.set(_center - _size);
		_max.set(_center + _size);
		break;
	}
}
