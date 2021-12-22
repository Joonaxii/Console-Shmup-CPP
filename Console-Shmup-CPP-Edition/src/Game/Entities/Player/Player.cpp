#include "windows.h"
#include "Player.h"
#include "../Entity.h"
#include "../../../Engine/Collision/Collider2D.h"
#include "../../../Engine/Math/Math.h"

const Vector2 Player::MAX_POS = Vector2(64.0f, 56.0f);
const Vector2 Player::MIN_POS = Vector2(-64.0f, -57.0f);


bool _mode(false);
Sprite* _spriteA(nullptr);
Sprite* _spriteB(nullptr);

Player::Player(const int stock, const int maxLives) : Entity("Player", true), _lifeStock(stock), _maxLives(maxLives) 
{ 
	_engine->getResourceManager()->tryGetSprite("Player", &_spriteA);
	_engine->getResourceManager()->tryGetSprite("Player_Up_Side", &_spriteB);

	_renderer->setSprite(_spriteA);
	_renderer->setLayer("Foreground");

	_transform->setRotation(0, true);
}
Player::~Player() { }

bool Player::update(const float delta) {
	float delt = Entity::update(delta);

	Vector2 pos(_transform->getPosition(true));
	Vector2 dir(0, 0);

	const auto inputs = _engine->getInputs();

	dir.x += inputs->isKeyHeld(Inputs::MOVE_RIGHT);
	dir.x -= inputs->isKeyHeld(Inputs::MOVE_LEFT);

	dir.y += inputs->isKeyHeld(Inputs::MOVE_UP);
	dir.y -= inputs->isKeyHeld(Inputs::MOVE_DOWN);

	dir.x *= delta * 48.0f;
	dir.y *= delta * 48.0f;

	pos += dir;

	pos.x = clamp(pos.x, MIN_POS.x, MAX_POS.x);
	pos.y = clamp(pos.y, MIN_POS.y, MAX_POS.y);
	_transform->setPosition(pos, true);

	const float r = repeat(_transform->getRotation(true), 360.0f);

	const float dL = abs(r);
	const float dR = abs(abs(r) - 180);
	const float d = min(dL, dR);

	const bool mod = d >= 45.0f;

	if (_mode != mod) {
		_mode = mod;
		_renderer->setSprite(_mode ? _spriteB : _spriteA);
	}

	_renderer->setSortingOrder(pos.y * -10);
	return delt;
}

void Player::onCollisionEnter(Collider2D& other) {
	//Entity* e = other.getOwnerAs<Entity>();

	//if (e != nullptr) {
	//	OutputDebugStringA("Is not null!");
	//	return;
	//}
	//OutputDebugStringA("Is null!");
}

void Player::onCollisionStay(Collider2D& other) { }
void Player::onCollisionExit(Collider2D& other) { }
