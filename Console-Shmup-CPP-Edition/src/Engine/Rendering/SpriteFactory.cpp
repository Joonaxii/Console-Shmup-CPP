#include "SpriteFactory.h"

//auto SpriteFactory::_boxSprites = {0};
//auto SpriteFactory::_circleSprites = {0};
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
	return nullptr;
}

Sprite* SpriteFactory::getCircle(const float raius, const float radiusSqrd) {

	return nullptr;
}
