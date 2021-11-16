#pragma once
#include "../Math/Vector2.h"
#include "../Core/Object.h"
#include "ColliderData.h"
#include "ColliderType.h"

class Collider2D
{
public:

	Collider2D(Object* owner);
	~Collider2D();

	template<class T> T* getOwnerAs() {
		return static_cast<T*>(_owner);
	}

	void updateColliderData(const ColliderData* colliderData, const unsigned char length);

	const bool isValid() const;
	bool collidesWith(const Collider2D& other);

	void setPosition(const Vector2& position);
	void update();

private:

	Object* _owner;

	Vector2 _position;

	Vector2 _min;
	Vector2 _max;

	unsigned char _numOfColliders;
	ColliderData* _colliderData;

	void clearColliderData();
};
