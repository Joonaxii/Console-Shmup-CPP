#include "SpriteFactory.h"

std::unordered_map<Vector2Int, Sprite*, Vector2Int::hasher> SpriteFactory::_boxSprites(0);
std::unordered_map<int, Sprite*, std::hash<int>> SpriteFactory::_circleSprites(0);
const char SpriteFactory::_ruleTiles[16] = {
	'½',  //0
	'|',  //1
	'-',  //2
	'/',  //3
	'|',  //4
	'|',  //5
	'\\', //6
	'|',  //7
	'-',  //8
	'\\', //9
	'-',  //10
	'-',  //11
	'/',  //12
	'|',  //13
	'-',  //14
	'½',  //15
};

Sprite* SpriteFactory::getBox(const float width, const float height) {
	Vector2Int reso((int)width, (int)height);

	auto f = _boxSprites.find(reso);
	if (f != _boxSprites.end()) {
		return _boxSprites[reso];
	}

	char* arr = new char[reso.x * reso.y];
	for (size_t y = 0; y < reso.y; y++)
	{
		int yCorner = y == 0 ? 1 : y == (reso.y-1 ) ? 2 : 0;
		for (size_t x = 0; x < reso.x; x++)
		{
			int i = y * reso.x + x;
			int xCorner = x == 0 ? 1 : x == (reso.x - 1) ? 2 : 0;

			if (xCorner == 0 && yCorner == 0) {
				arr[i] = '\0';
				continue;
			}

			switch (xCorner)
			{
			case 1:
			case 2:
				switch (yCorner)
				{
				case 0:
					arr[i] = '|';
					break;
				case 1:
				case 2:
					arr[i] = '-';
					break;
				}
				break;
			case 0:
				arr[i] = '-';
				break;
			}
		}
	}

	Sprite* sprt = new Sprite(arr, reso, Vector2(0.5f, 0.5f), 0);
	_boxSprites.insert(std::pair<Vector2Int, Sprite*>(reso, sprt));
	
	delete[] arr;
	return sprt;
}

Sprite* SpriteFactory::getCircle(const float raius, const float radiusSqrd) {

	return nullptr;
}
