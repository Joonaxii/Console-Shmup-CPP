#pragma once
#include "ColliderType.h"


class Collider2D
{
public:

	Collider2D();
	~Collider2D();

	bool collidesWith(const Collider2D& other);

private:

	void* _owner;

	Vector2 _position;

	Vector2 _min;
	Vector2 _max;

	ColliderType _type;
	Vector2 _size;
	float _radSqrd;

};

