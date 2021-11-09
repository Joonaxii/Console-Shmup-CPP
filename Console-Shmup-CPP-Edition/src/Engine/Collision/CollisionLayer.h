#pragma once
#include <type_traits>

enum struct CollisionLayer : int
{
	None = 0,

	Player = 1,
	PlayerBullet = 2,

	Enemy = 3,
	EnemyBullet = 4,

	World = 5,
};
//
//inline CollisionLayer operator |(CollisionLayer lhs, CollisionLayer rhs)
//{
//	using T = std::underlying_type_t<CollisionLayer>;
//	return static_cast<CollisionLayer>(static_cast<T>(lhs) | static_cast<T>(rhs));
//}


