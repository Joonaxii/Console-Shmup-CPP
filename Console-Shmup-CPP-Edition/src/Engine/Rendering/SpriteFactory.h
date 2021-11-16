#pragma once
#include <unordered_map>
#include "Sprite.h"
#include "../Math/Vector2Int.h"

class SpriteFactory
{
public:
	static Sprite* getBox(const float width, const float height);
	static Sprite* getCircle(const float raius, const float radiusSqrd);

private:
	static const char _ruleTiles[16];

	static std::unordered_map<Vector2Int, Sprite*, Vector2Int::hasher> _boxSprites;
	static std::unordered_map<int, Sprite*, std::hash<int>> _circleSprites;
};

