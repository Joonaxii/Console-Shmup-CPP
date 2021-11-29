#pragma once
#include "CollisionGrid.h"
#include "../Math/Vector2.h"
#include "../Core/Object.h"
#include "CollisionSystem.h"
#include "ColliderData.h"
#include "ColliderType.h"
#include "CollisionGlobals.h"
#include <unordered_set>
#include "../Components/Transform.h"

class Collider2D
{
public:

	std::function<void(Collider2D*)> onEnter;
	std::function<void(Collider2D*)> onStay;
	std::function<void(Collider2D*)> onExit;

	Collider2D(Object* owner, Transform* transform);
	~Collider2D();

    template<class T> T* getOwnerAs() const{
		return static_cast<T*>(_owner);
	}

	const unsigned int getID() const;

	void updateColliderData(const ColliderData* colliderData, const unsigned char length);

	const bool isValid() const;
	const bool collidesWith(const Collider2D& other) const;

	void setPosition(const Vector2& position);
	void update();

	void clear();

    bool addCollision(const Collider2D* other);
    bool removeCollision(const Collider2D* other);
    bool hasCollision(const Collider2D* other) const;

private:

	Object* _owner;
	Transform* _transform;

	Vector2 _position;

	Vector2 _min;
	Vector2 _max;

	unsigned int _id;

	unsigned long long _chunkMask;
	unsigned long long _chunkNodeMasks[CHUNK_COUNT];

	unsigned char _numOfColliders;
	ColliderData* _colliderData;

	std::vector<Collider2D*> _collisions;
	std::unordered_set<int> _collisionSet;

	void clearColliderData();
};
