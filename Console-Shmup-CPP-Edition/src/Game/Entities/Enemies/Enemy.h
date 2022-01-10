#pragma once
#include "../Entity.h"

class Enemy : public Entity
{
public:
	Enemy(const std::string name, const bool hasCollider, const int maxHP);
	~Enemy();

	virtual bool update(const float delta);

protected:

	int _maxHp;

	virtual void onCollisionEnter(Collider2D& other);
	virtual void onCollisionStay(Collider2D& other);
	virtual void onCollisionExit(Collider2D& other);

};

