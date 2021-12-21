#include "GenericEntity.h"

GenericEntity::GenericEntity(const std::string name, Sprite* sprite, const std::string layer, const bool sortByY, const short sortingOrderOffset) : Entity(name), _sortByY(sortByY), _sortingOffset(sortingOrderOffset) {
	_renderer->setLayer(layer);
	_renderer->setSprite(sprite);
	_renderer->setActive(true);

	if (!_sortByY) {
		_renderer->setSortingOrder(sortingOrderOffset);
	}
}

GenericEntity::~GenericEntity()  {
	Object::~Object();
}

bool GenericEntity::update(const float delta) {
	if (_sortByY) {
		_renderer->setSortingOrder(_transform->getPosition(true).y * -10 + _sortingOffset);
	}
	return true;
}

void GenericEntity::onCollisionEnter(Collider2D& other) { }
void GenericEntity::onCollisionStay(Collider2D& other) { }
void GenericEntity::onCollisionExit(Collider2D& other) { }
