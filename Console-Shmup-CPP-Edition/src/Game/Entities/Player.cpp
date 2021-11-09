#include "windows.h"
#include "Player.h"
#include "Entity.h"
#include "../../Engine/Collision/Collider2D.h"

Player::Player() { }
Player::~Player() { }

void Player::onCollisionEnter(Collider2D& other) {
	Entity* e = other.getOwnerAs<Entity>();

	if (e != nullptr) {
		OutputDebugStringA("Is not null!");
		return;
	}
	OutputDebugStringA("Is null!");
}

void Player::onCollisionStay(Collider2D& other) { }
void Player::onCollisionExit(Collider2D& other) { }
