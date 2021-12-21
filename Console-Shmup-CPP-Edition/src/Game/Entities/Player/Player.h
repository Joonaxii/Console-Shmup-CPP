#pragma once
#include "../../../Engine/Collision/Collider2D.h"
#include "../Entity.h"

class Entity;
class Player : public Entity
{
	public:
		Player(const int stock, const int maxLives);
		~Player();

	 bool update(const float delta);

protected:

	virtual void onCollisionEnter(Collider2D& other);
	virtual void onCollisionStay(Collider2D& other);
	virtual void onCollisionExit(Collider2D& other);

private:

	static const Vector2 MAX_POS;
	static const Vector2 MIN_POS;

	int _maxLives;
	int _lifeStock;
};

