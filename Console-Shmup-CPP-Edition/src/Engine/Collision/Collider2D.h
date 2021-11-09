#pragma once
#include "../Core/Vector2.h"
#include "ColliderData.h"
#include "ColliderType.h"

class Collider2D
{
public:

	Collider2D();
	~Collider2D();

	template<class T> T* getOwnerAs() {
		return static_cast<T*>(_owner);
	}

	bool collidesWith(const Collider2D& other);

private:

	void* _owner;

	Vector2 _position;

	Vector2 _min;
	Vector2 _max;

	int _numOfColliders;
	ColliderData* _colliderData;
};
