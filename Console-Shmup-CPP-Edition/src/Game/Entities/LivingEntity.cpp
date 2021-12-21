#include "LivingEntity.h"

LivingEntity::LivingEntity() : Entity(), _maxHP(0), _curentHP(0), _isDead(true) { }
LivingEntity::~LivingEntity() { 
	Object::~Object();
}

void LivingEntity::kill(bool silent, Object* killer) {
}

bool LivingEntity::takeDamage(const int damage, Object* damageDealer) {
	return false;
}

void LivingEntity::setMaxHP(const int newHP, const bool setCurrent) {
	_maxHP = newHP;

	if (!setCurrent) { return; }
	_curentHP = newHP;
}