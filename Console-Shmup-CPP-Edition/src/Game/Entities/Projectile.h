#pragma once
#include "Entity.h"

class Projectile : public Entity {

public:
	Projectile();
	~Projectile();

	virtual bool update(const float delta);

protected:

	virtual void onCollisionEnter(Collider2D& other);
	virtual void onCollisionStay(Collider2D& other);
	virtual void onCollisionExit(Collider2D& other);
};

