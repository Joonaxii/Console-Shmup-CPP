#define NOMINMAX
#include <limits>
#include "CollisionSystem.h"
#include "Collider2D.h"
#include "../Rendering/Sprite.h"
#include "../Core/Object.h"
#include "../Rendering/Rendering.h"
#include "../Rendering/SpriteFactory.h"

bool Collider2D::SHOW_BOUNDS = false;

Collider2D::Collider2D(Object* owner, Transform* transform) : _chunkMask(0), _chunkNodeMasks{0}, _transform(transform) , _min(0, 0), _max(0, 0), _numOfColliders(0), _colliderData(nullptr), _owner(owner)  {
	_id = CollisionSystem::registerCollider(this);
}

Collider2D::~Collider2D() 
{ 
	clearColliderData(); 
}

const unsigned int Collider2D::getID() const {
	return _id;
}

void Collider2D::updateColliderData(const ColliderData* colliderData, const unsigned char length) {
	
	if (length != _numOfColliders) {
		clearColliderData();

		_numOfColliders = length;
		_colliderData = new ColliderData[_numOfColliders];
	}

	for (size_t i = 0; i < length; i++) { _colliderData[i].copyFrom(colliderData[i]); }
}

const bool Collider2D::isValid() const { return _owner == nullptr || _numOfColliders < 1 || _colliderData == nullptr; }

const bool Collider2D::collidesWith(const Collider2D& other) const {
	if (!isValid() || !other.isValid()) { return false; }
	if (_owner->getID() == other._owner->getID()) { return false; }
	if (!CollisionSystem::aabbVsAABB(_min, _max, other._min, other._max)) { return false; }

	for (size_t i = 0; i < _numOfColliders; i++)
	{
		const auto cA = _colliderData[i];
		for (size_t j = 0; j < other._numOfColliders; j++)
		{
			const auto cB = other._colliderData[j];
			if (cA.collidesWith(cB)) { return true; }
		}
	}
	return false;
}

void Collider2D::setPosition(const Vector2& position) {
	_position.set(position);
	update();
}

void Collider2D::update() {
	_min.x = _min.y = std::numeric_limits<float>().max();
	_max.x = _max.x = std::numeric_limits<float>().min();

	for (size_t i = 0; i < _numOfColliders; i++) {
		auto c = _colliderData[i];
		c.update(_position);

		const auto cMin = c.getMin();
		const auto cMax = c.getMax();

		_min.x = std::min(_min.x, cMin.x);
		_min.y = std::min(_min.y, cMin.y);

		_max.x = std::max(_max.x, cMax.x);
		_max.y = std::max(_max.y, cMax.y);
	}

	if (SHOW_BOUNDS) {
		Sprite* sprt = SpriteFactory::getBox(_max.x - _min.x, _max.y - _min.y);
		Rendering::drawSprite(sprt, _position, "Debug", (short)(_position.y * -10));
	}
}

void Collider2D::clear() {
	memset(_chunkNodeMasks, 0, sizeof(unsigned long long) * CHUNK_COUNT);
	_chunkMask = 0;
}

bool Collider2D::addCollision(const Collider2D* other) {
	return false;
}

bool Collider2D::removeCollision(const Collider2D* other) {
	return false;
}

bool Collider2D::hasCollision(const Collider2D* other) const {
	return _collisionSet.find(other->getID()) != _collisionSet.end();
}

bool Collider2D::validateChunk(const ulong chunkBit) {
	if ((_chunkMask & chunkBit) != 0) { return false; }

	_chunkMask |= chunkBit;
	return true;
}

void Collider2D::clearColliderData() {
	if (_colliderData == nullptr) { return; }
	
	delete[] _colliderData;

	_numOfColliders = 0;
	_colliderData = nullptr;
}

