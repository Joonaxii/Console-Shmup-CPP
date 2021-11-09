#pragma once
#include "../../Engine/Collision/Collider2D.h"
#include "Entity.h"

class Entity;
class Player : public Entity
{
	public:
		Player();
		~Player();

protected:

	virtual void onCollisionEnter(Collider2D& other);
	virtual void onCollisionStay(Collider2D& other);
	virtual void onCollisionExit(Collider2D& other);
};

