#pragma once
#include "../Core/Vector2.h"
#include "ColliderType.h"

class ColliderData
{
public:

	ColliderData();

	ColliderData(const Vector2 offset);
	ColliderData(const Vector2 offset, const float radius);
	ColliderData(const Vector2 offset, const Vector2 size);

	const Vector2 getMin() const;
	const Vector2 getMax() const;

	const bool collidesWith(const ColliderData& other) const;
    void copyFrom(const ColliderData& other);

	void update(Vector2& center);

private:

	Vector2 _center;

	Vector2 _min;   
	Vector2 _max;   

	ColliderType _type;

	Vector2 _offset;   
	Vector2 _size;     

	float _radSqrd;    

};

