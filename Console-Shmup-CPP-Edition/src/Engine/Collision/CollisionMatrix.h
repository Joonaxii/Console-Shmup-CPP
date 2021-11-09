#pragma once
#include "CollisionLayer.h"

class CollisionMatrix
{
public:
	static bool canCollide(const CollisionLayer& layer, const CollisionLayer& other);
private:
	static const int _matrix[];
};

