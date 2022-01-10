#include "Enemy.h"

Enemy::Enemy(const std::string name, const bool hasCollider, const int maxHP) : Entity(name, hasCollider), _maxHp(maxHP) { }
Enemy::~Enemy() {
    Entity::~Entity();
}

bool Enemy::update(const float delta) {
    const bool temp = Entity::update(delta);
    return temp;
}

void Enemy::onCollisionEnter(Collider2D& other) { }
void Enemy::onCollisionStay(Collider2D& other) { }
void Enemy::onCollisionExit(Collider2D& other) { }
