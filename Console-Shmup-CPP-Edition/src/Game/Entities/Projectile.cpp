#include "Projectile.h"

bool Projectile::update(const float delta) {
    Entity::update(delta);
    return false;
}

void Projectile::onCollisionEnter(Collider2D& other) {

}

void Projectile::onCollisionStay(Collider2D& other) {
}

void Projectile::onCollisionExit(Collider2D& other) {

}
