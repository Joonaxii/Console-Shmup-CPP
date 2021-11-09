#include "CollisionMatrix.h"
#include "CollisionLayer.h"

const int CollisionMatrix::_matrix[] = { 
	0,																					//None
	
	(1 << (int)CollisionLayer::EnemyBullet),											//Player
	(1 << (int)CollisionLayer::Enemy)		| (1 << (int)CollisionLayer::World),        //PlayerBullet

	(1 << (int)CollisionLayer::PlayerBullet),											//Enemy
	(1 << (int)CollisionLayer::Player)		| (1 << (int)CollisionLayer::World),		//Enemy Bullet

	(1 << (int)CollisionLayer::EnemyBullet) | (1 << (int)CollisionLayer::PlayerBullet), //World
};

bool CollisionMatrix::canCollide(const CollisionLayer& mask, const CollisionLayer& layer) {
	const int lr = 1 << (int)layer;
	return (_matrix[(int)mask] & lr) == lr;
}
