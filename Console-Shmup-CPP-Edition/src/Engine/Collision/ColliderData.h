#pragma once
#include "../Core/Vector2.h"
#include "ColliderType.h"

class ColliderData
{
public:
	ColliderData();
	ColliderData(Vector2 offset);
	ColliderData(Vector2 offset, float radius);
	ColliderData(Vector2 offset, Vector2 size);

	void update(Vector2& center);
	bool collidesWith(const ColliderData& other);

private:

	Vector2 _center;

	Vector2 _min;   
	Vector2 _max;   

	ColliderType _type;

	Vector2 _offset;   
	Vector2 _size;     

	float _radSqrd;    

};

