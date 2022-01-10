#include "Game.h"
#include "../Engine/Math/Math.h"
#include "Entities/GenericEntity.h"
#include "../Engine/Rendering/Animator.h"
#include "Entities/Tether.h"
#include "Entities/Enemies/Boss_2/Boss2Head.h"

const int Game::SWORD_COUNT = 64;
const int Game::CONFIG_COUNT = 5;
const float Game::_orientationConfigs[Game::CONFIG_COUNT]{
		-364.0f,
		-145.0f,
		-95.0f,
		-155,
		-115.0f,
};
const float Game::_bladeConfigs[Game::CONFIG_COUNT]{
		-4.0f,
		-6.0f,
		-135.0f,
		-65,
		55.0f,
};
const float Game::_bladeSpeeds[Game::CONFIG_COUNT]{
		1.25f,
		2.75f,
		-1.0f,
		1.0f,
		-2.0f,
};

const float Game::_plrRotations[Game::CONFIG_COUNT]{
		90,
		90,
		90,
		90,
		90,
		//180.0f,
		//270.0f,
		//360.0f + 90.0f,
};

const float Game::_laserWidthConf[Game::CONFIG_COUNT]{
		0.0f,
		0.45f,
		1.0f,
		2.0f,
		0.45f,
		//180.0f,
		//270.0f,
		//360.0f + 90.0f,
};

Animator** laserAnims;
Transform* laserRoot;
Boss2Head* enemy;

Boss2Head* enemyB;
Boss2Head* enemyC;

const int LASER_COUNT(0);
bool temp(false);
Game::Game() {
    _engine = Engine::getInstance();
    _inputs = _engine->getInputs();
    _rendering = _engine->getRendering();

    _engine->addListener([this]() { update(); });
	_player = new Player(5, 20);

	_plrRootTransform = new Transform();
	//_player->getTransform()->addChild(_plrRootTransform);

	Sprite* sprtB(nullptr);
	_engine->getResourceManager()->tryGetSprite("Boss_Sword", &sprtB);

	_swords = new GenericEntity*[SWORD_COUNT];
	_swordAngles = new float[SWORD_COUNT];

	Transform* target = new Transform();
	target->setPosition(Vector2(0, -60), true);
	enemy = new Boss2Head(-1000, 1.0f, 0.0f, target, 100);
	const short OFF = enemy->getRenderDepth();

	enemyB = new Boss2Head(-1000 - OFF, -1.0f, 45.0f, target, 100);
	enemyC = new Boss2Head(-1000 - OFF, -1.0f, 90.0f, target, 100);

	enemyB->setFollowTarget(_player->getTransform());
	enemyC->setFollowTarget(_player->getTransform());

	enemyB->setTargetOffset(Vector2(-40, 18));
	enemyC->setTargetOffset(Vector2(40, 18));
	
	enemyB->setFollowSpeed(0.5f);
	enemyC->setFollowSpeed(0.5f);

	enemyB->setFollowPower(Vector2(0.45f, 0.65f));
	enemyC->setFollowPower(Vector2(0.45f, 0.65f));

	enemyB->setMinMaxPos(Vector2(-56.0f, 10.0f), Vector2(56.0f, 50.0f));
	enemyC->setMinMaxPos(Vector2(-56.0f, 10.0f), Vector2(56.0f, 50.0f));

	enemyB->setRotationPower(0.5f);
	enemyC->setRotationPower(0.5f);

	GenericEntity** laser = new GenericEntity* [LASER_COUNT];
    laserAnims = new Animator* [LASER_COUNT];

	Animation* animLaserHead;
	Animation* animLaserLoop;

	_engine->getResourceManager()->tryGetAnimation("Laser_Head_Loop", &animLaserHead);
	_engine->getResourceManager()->tryGetAnimation("Laser_Loop", &animLaserLoop);

	laserRoot = new Transform();

	enemy->getTransform()->addChild(laserRoot);
	enemy->setTargetOffset(Vector2(0, 28));
	enemy->setFollowTarget(_player->getTransform());

	laserRoot->setPosition(Vector2(0, -42.0f), false);
	laserRoot->setRotation(90, false);
	for (size_t i = 0; i < LASER_COUNT; i++)
	{
		GenericEntity* laser = new GenericEntity("LASER", nullptr, false, "EnemiesBG", false, -5 - i);
		const Vector2 pos(-30.0f * i, 0);
		auto an = laserAnims[i] = new Animator(laser->getRenderer(), 1.0f);

		auto tra = laser->getTransform();
		laserRoot->addChild(tra);
		tra->setPosition(pos, false);

		if (i == 0) {
			an->addAnimation(animLaserHead);
		}
		else {
			an->addAnimation(animLaserLoop);
		}
		an->play(0);
	}

	const int NECK_COUNT = 8;
	const float START_NECK_SIZE = 0.15f;
	/*GenericEntity** neck = new GenericEntity*[NECK_COUNT];

	for (size_t i = 0; i < NECK_COUNT; i++)
	{
		auto nck = neck[i] = new GenericEntity("Neck", enemyNeck, "EnemiesBG", false, -5 - i);
		enemy->getTransform()->addChild(nck->getTransform());
		const float scal = lerp(START_NECK_SIZE, 1.0f, i / (NECK_COUNT - 1.0f));
		nck->getTransform()->setScale(Vector2(scal, scal), false);
		nck->getTransform()->setPosition(Vector2(0, -12 - (i * scal * 9)), false);
	}*/

	enemy->getTransform()->setPosition(Vector2(0, 4), true);

	const float radPerI = (360.0f / SWORD_COUNT);
	for (size_t i = 0; i < SWORD_COUNT; i++)
	{
		float ang = radPerI * i;
		float rads = ang * DEG_2_RAD;

		auto tr = (_swords[i] = new GenericEntity("Sword #" + std::to_string(i), sprtB, false, "Foreground"))->getTransform();
		_swords[i]->getRenderer()->setActive(false);
		_plrRootTransform->addChild(tr);
		tr->setPosition(Vector2(cosf(rads) * 24.0f, sinf(rads) * 24.0f), false);
		tr->setRotation(ang, false);

		_swordAngles[i] = ang;
	}
}

Game::~Game() { }

bool _transitioning(true);
float _configTime;

float valRot(-360.0f);
float valBlade(0);
float valBladeSpd(0);
float valPlrRot(0);
float transitionSpeed(0);

float laserWidth(1.0f);

float valRotST(-360.0f);
float valBladeST(0);
float valBladeSTSpd(0);
float valPlrSTRot(0.0f);

float laserWidthST(0);

int currentConfig(0);

Vector2 velocity(0, 0);

void Game::update() {

	const auto mainT = _engine->getThread(EngineThreadType::Main);
	const auto renderT = _engine->getThread(EngineThreadType::Render);

	const Time* timeMain = _engine->getTime(EngineThreadType::Main);
	const Time* timeRender = _engine->getTime(EngineThreadType::Render);
	const CollisionSystem* collSystem = _engine->getCollisionSystem();

	if (_inputs->isKeyDown(Inputs::DEBUG_MODE)) {
		SpriteRenderer::DRAW_BOUNDS = !SpriteRenderer::DRAW_BOUNDS;
	}
		
	if (_inputs->isKeyDown(Inputs::DEBUG_MODE_MISC)) {
		Collider2D::SHOW_BOUNDS = !Collider2D::SHOW_BOUNDS;
	}

	float delta = timeMain->getDeltaTime();
	_player->update(delta);

	enemy->update(delta);
	enemyB->update(delta);
	enemyC->update(delta);
	for (size_t i = 0; i < LASER_COUNT; i++)
	{
		laserAnims[i]->update(delta);
	}

	float n;
	if (_transitioning) {
		_configTime += delta;
		n = clamp(_configTime / _configTransitionDuration, 0.0f, 1.0f);

		valRot = lerp(valRotST, _orientationConfigs[currentConfig], n);
		valBlade = lerp(valBladeST, _bladeConfigs[currentConfig], n);
		valBladeSpd = lerp(valBladeSTSpd, _bladeSpeeds[currentConfig], n);
		valPlrRot = lerpAngle(valPlrSTRot, _plrRotations[currentConfig], n);
		laserWidth = lerp(laserWidthST, _laserWidthConf[currentConfig], n);
		transitionSpeed = lerp(1.0f, 1.0f, clamp(n * 4.0f, 0.0f, 1.0f));

		_player->getTransform()->setRotation(valPlrRot, false);

		laserRoot->setScale(Vector2(1.0f, laserWidth), false);

		if (n >= 1.0f) {

			currentConfig++;
			currentConfig = currentConfig % CONFIG_COUNT;

			_transitioning = false;
			_configTime = 0;
		}
	}
	else {
		_configTime += delta;

		//_transitonSpeed = lerp(1.0f, 1.0f, clamp((_configTime / _configDuration) * 8.0f, 0.0f, 1.0f));
		if (_configTime >= _configDuration) {
			_configTime = 0;
			_transitioning = true;

			valRotST = valRot;
			valBladeST = valBlade;
			valBladeSTSpd = valBladeSpd;
			valPlrSTRot = valPlrRot;
			laserWidthST = laserWidth;
		}
	}
	_plrRootTransform->setPosition(_player->getTransform()->getPosition(true), false);
	_plrRootTransform->setRotation(_t, false);

	Rendering::MAIN_CAMERA->setPosition(_player->getTransform()->getPosition(true) * 0.1f, true);

	const int wingCount = 16;
	const int diff = SWORD_COUNT / wingCount;
	for (size_t i = 0; i < SWORD_COUNT; i++)
	{
		auto swrd = _swords[i];
		auto tr = swrd->getTransform();
		const float val = _swordAngles[i];

		float ii = ((i % diff) / (float)diff) * diff;

		tr->setRotation(val + valRot + ((ii * valBlade)), false);
		swrd->update(delta);
	}

	const auto frm = timeMain->getFrames();
	if (frm % 4 == 0) {
		auto tm = (mainT->getIsWaiting() ? " [W]: " : ": ");
		_rendering->addInfoString(0, 0, ("Fps (Main)" + std::string(tm) + std::to_string(timeMain->getFramerate()) + "      ").c_str());
		_rendering->addInfoString(0, 1, ("Time (Main): " + std::to_string(timeMain->getTime()) + "      ").c_str());

	    tm = (renderT->getIsWaiting() ? " [W]: " : ": ");
		_rendering->addInfoString(0, 4, ("Fps (Render)" + std::string(tm) + std::to_string(timeRender->getFramerate()) + "      ").c_str());
		_rendering->addInfoString(0, 5, ("Time (Render): " + std::to_string(timeRender->getTime()) + "      ").c_str());

		_rendering->addInfoString(0, 7, ("Collider Count: " + std::to_string(collSystem->getColliderCount()) + "      ").c_str());

		const auto pos = _player->getTransform()->getPosition(true);
		const Vector2Int inBuffer((int)std::roundf(pos.x), (int)std::roundf(pos.y));
		_rendering->addInfoString(0, 8, ("Plr Pos Wrld: " + pos.toString() + "  ||  Buf: " +  inBuffer.toString() + "  ").c_str());
		//rend->addInfoString(0, 2, ("Delta: " + std::to_string(timeMain->getDeltaTime()) + "     ").c_str());
		//rend->addInfoString(0, 3, ("Frames: " + std::to_string(frm) + "     ").c_str());
	}
}
