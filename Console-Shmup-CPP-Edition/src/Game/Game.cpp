#include "Game.h"
#include "../Engine/Math/Math.h"
#include "Entities/GenericEntity.h"
#include "../Engine/Rendering/Animator.h"
#include "Entities/Tether.h"

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

GenericEntity* enemy;
GenericEntity* fangB;
GenericEntity* fangA;
Animator** laserAnims;
Transform* laserRoot;
Tether* _neck;
const int LASER_COUNT(17);
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

	Sprite* enemySprt(nullptr);
	Sprite* enemyFang(nullptr);
	Sprite* enemyNeck(nullptr);
	Sprite* enemyBody(nullptr);

	_engine->getResourceManager()->tryGetSprite("Boss_2_Head", &enemySprt);
	_engine->getResourceManager()->tryGetSprite("Boss_2_Fang", &enemyFang);
	_engine->getResourceManager()->tryGetSprite("Boss_2_Body", &enemyBody);
	_engine->getResourceManager()->tryGetSprite("Boss_2_Neck", &enemyNeck);

	enemy = new GenericEntity("Enemy", enemySprt, true, "EnemiesBG", false, 0);
	fangA = new GenericEntity("Fang A", enemyFang, false, "EnemiesBG", false, -2);
	fangB = new GenericEntity("Fang B", enemyFang, false, "EnemiesBG", false, -2);
	auto body = new GenericEntity("Body", enemyBody, false, "EnemiesBG", false, -2000);

	body->getTransform()->setPosition(Vector2(0, -58), true);

	Transform* bodyNeckPos = new Transform();
	body->getTransform()->addChild(bodyNeckPos);
	bodyNeckPos->setPosition(Vector2(0.0f, 46.0f), false);

	_neck = new Tether(8, 5.0f, 0.85f, 0.75f, 0.25f, WaveSpecifications(WaveType::Sine, 0, 4.5f, 0.5f), -15.0f, 25.0f);
	_neck->setSprite(enemyNeck, "EnemiesBG", -1600);
	_neck->setPoint(bodyNeckPos, Vector2::zero, true);
	_neck->setPoint(enemy->getTransform(), Vector2(0, 2.5f), false);

	GenericEntity** laser = new GenericEntity* [LASER_COUNT];
    laserAnims = new Animator* [LASER_COUNT];

	Animation* animLaserHead;
	Animation* animLaserLoop;

	_engine->getResourceManager()->tryGetAnimation("Laser_Head_Loop", &animLaserHead);
	_engine->getResourceManager()->tryGetAnimation("Laser_Loop", &animLaserLoop);

	laserRoot = new Transform();

	enemy->getTransform()->addChild(laserRoot);
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

	enemy->getTransform()->addChild(fangA->getTransform());
	enemy->getTransform()->addChild(fangB->getTransform());

	fangA->getTransform()->setPosition(Vector2(-8, -2), false);
	fangB->getTransform()->setPosition(Vector2(8, -2), false);

	fangB->getRenderer()->setFlipX(true);

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
	const float t = timeMain->getTime() * 50.0f;
	const float tS = lerp(-15, 15, (sinf(t * DEG_2_RAD * 2.0f) + 1.0f) * 0.5f);

	const float rot = lerp(-10.0f, 25.0f, (sinf(t * 3.5f * DEG_2_RAD * 2.0f) + 1.0f) * 0.5f);
	const float rotA = lerp(-15.0f, 15.0f, (sinf(t * 1.75f*0.5f * DEG_2_RAD * 2.0f) + 1.0f) * 0.5f);
	const float posB = lerp(-1.5f, 3.0f, (sinf(t * 1.75f * DEG_2_RAD * 2.0f) + 1.0f) * 0.5f);

	fangA->getTransform()->setRotation(rot, false);
	fangB->getTransform()->setRotation(-rot, false);

	Vector2 enPos(enemy->getTransform()->getPosition(true));

	const Vector2 plrPos(_player->getTransform()->getPosition(true));

	enPos = Vector2::lerp(enPos, Vector2(plrPos.x * 0.75f, clamp(plrPos.y * 0.65f, -0.25f, 35.0f) + 28.0f + posB), delta * 2.8f);
	enemy->getTransform()->setPosition(enPos, true);

	const float angleE = enemy->getTransform()->getRotation(false);
	const float angl((plrPos - enPos).angleDegrees(Vector2(0, -1.0f), true));
	enemy->getTransform()->setRotation(lerpAngle(angleE, clamp(angl + rotA, -85.0f, 85.0f), delta * 4.0f), false);

	_neck->update(delta);
	_t += delta * -150.0 * valBladeSpd;
	_player->update(delta);

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
