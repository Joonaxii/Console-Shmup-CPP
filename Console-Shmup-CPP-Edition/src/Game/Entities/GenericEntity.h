#pragma once
#include "Entity.h"
#include "../../Engine/Rendering/Sprite.h"

class GenericEntity : public Entity
{
public:
	GenericEntity(const std::string name, Sprite* sprite, const bool hasCollider, const std::string layer, const bool sortByY = true, const short sortingOrderOffset = 0);
	~GenericEntity();

	bool update(const float delta);

protected:

	short _sortingOffset;
	bool _sortByY;

	virtual void onCollisionEnter(Collider2D& other);
	virtual void onCollisionStay(Collider2D& other);
	virtual void onCollisionExit(Collider2D& other);
};

