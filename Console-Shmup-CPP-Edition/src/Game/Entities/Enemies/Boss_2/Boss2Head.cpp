#include "Boss2Head.h"
#include "../../../../Engine/Math/Math.h"

Boss2Head::Boss2Head() : Boss2Head(0, 1.0f, 0.0f, nullptr, 100) { }
Boss2Head::Boss2Head(const short baseSortingOrder, const float direction, const float phaseOffset, Transform* target, const int maxHP) : Enemy("Boss 2 Head", false, maxHP),
_timeOffset(phaseOffset), _direction(direction), _rotatePower(1.0f),
_rotationSpeed(1.0f), _followSpeed(2.0f), _targetB(nullptr), _followTarget(nullptr),
_restingPos(0, 0), _offsetToTarget(0, 0), _lookAtTarget(true), _followPower(0.75f, 0.65f), _minPos(-99999.0f, 15.5f), _maxPos(99999.0f, 52.5f),

_fadingMode(0), _staticFadeDuration(0.0f), _staticT(0.0f), _staticInterp(1.0f), _rotateVelo(0.0f)
{
    Transform* neckTgt(target != nullptr ? target : _targetB = new Transform());

    if (_targetB != nullptr) {
        _targetB->setPosition(Vector2(0, -60), false);
    }

    const short NECK_LEN = 12;
    _renderDepth = (NECK_LEN + 2);
    const short REND_COUNT = _renderDepth + baseSortingOrder;

    Sprite* enemySprt(nullptr);
    Sprite* enemyFang(nullptr);
    Sprite* enemyNeck(nullptr);

    _engine->getResourceManager()->tryGetSprite("Boss_2_Head", &enemySprt);
    _engine->getResourceManager()->tryGetSprite("Boss_2_Fang", &enemyFang);
    _engine->getResourceManager()->tryGetSprite("Boss_2_Neck", &enemyNeck);

    _neck = new Tether(phaseOffset, direction, NECK_LEN, 8.0f, 1.0f, 1.25f, 0.35f, WaveSpecifications(WaveType::Sine, 0, 4.0f, 0.5f), -35.0f, 25.0f);

    _neck->setPoint(neckTgt, Vector2::zero, true);
    _neck->setPoint(_transform, Vector2::zero, false);
    _neck->setSprite(enemyNeck, "EnemiesBG", REND_COUNT - 2);

    _fangA = new GenericEntity(_name + " Fang A", enemyFang, false, "EnemiesBG", false, REND_COUNT - 1);
    _fangB = new GenericEntity(_name + " Fang B", enemyFang, false, "EnemiesBG", false, REND_COUNT - 1);

    _transform->addChild(_fangA->getTransform());
    _transform->addChild(_fangB->getTransform());

    _fangA->getTransform()->setPosition(Vector2(-8, -2), false);
    _fangB->getTransform()->setPosition(Vector2(8, -2), false);

    _fangB->getRenderer()->setFlipX(true);

    _renderer->setSprite(enemySprt);
    _renderer->setLayer("EnemiesBG");
    _renderer->setSortingOrder(REND_COUNT);
}

Boss2Head::~Boss2Head() {
    Enemy::~Enemy();

    if (_targetB != nullptr) {
        delete _targetB;
    }

    delete _neck;

    delete _fangA;
    delete _fangB;
}

const short Boss2Head::getRenderDepth() const {
    return _renderDepth;
}

bool Boss2Head::update(const float delta) {
    if (Enemy::update(delta)) {
        handleStaticInterp(delta);

        Vector2 pos(_transform->getPosition(true));
        const float rot(_transform->getRotation(true));

        const Vector2 tgt(_followTarget != nullptr ? _followTarget->getPosition(true) : pos - Vector2(0, -10));
        Vector2 targetPos(_followTarget != nullptr ? _followTarget->getPosition(true) * _followPower + _offsetToTarget : _restingPos);
        targetPos.x = clamp(targetPos.x, _minPos.x, _maxPos.x);
        targetPos.y = clamp(targetPos.y, _minPos.y, _maxPos.y);

        float t = _time * 45.0f + _timeOffset;

        Vector2 inf(infinity(t * DEG_2_RAD) * _direction);
        inf.x = lerp(-8.0f, 8.0f, (inf.x + 1.0f) * 0.5f);
        inf.y = lerp(-3.0f, 6.0f, (inf.y + 1.0f) * 0.5f);
        const Vector2 offset(inf * _staticInterp);

        pos = Vector2::smoothDamp(pos, targetPos + offset, &_velocity, _followSpeed, delta);

        const float rotFang = lerp(-10.0f, 25.0f, (sinf(t * 3.5f * DEG_2_RAD * 2.0f) + 1.0f) * 0.5f) * _staticInterp;
        const float targetRot = clamp(_lookAtTarget ? (tgt - pos).angleDegrees(Vector2(0, -1.0f), true) * _rotatePower : 0.0f, -85.0f, 85.0f);

        _fangA->getTransform()->setRotation(rotFang, false);
        _fangB->getTransform()->setRotation(-rotFang, false);

        _transform->setPosition(pos, true);
        _transform->setRotation(smoothDamp(rot, targetRot, &_rotateVelo, _rotationSpeed, delta), true);

        _neck->update(delta);
        return true;
    }
    return false;
}

void Boss2Head::setFollowPower(const Vector2& power) {
    _followPower.set(power);
}

void Boss2Head::setRotationPower(const float power) {
    _rotatePower = power;
}

void Boss2Head::setFollowSpeed(const float speed) {
    _followSpeed = speed;
}

void Boss2Head::setRotationSpeed(const float speed) {
    _rotationSpeed = speed;
}

void Boss2Head::setStatic(const bool isStatic, const float duration) {

    if (duration <= 0) {
        _staticInterp = isStatic ? 0.0f : 1.0f;
        _staticT = 0.0f;
        _staticFadeDuration = 0;
        _fadingMode = 0;
        return;
    }

    switch (_fadingMode)
    {
    case 1:
        if (isStatic) { return; }
        break;

    case 2:
        if (!isStatic) { return; }
        break;
    }

    _staticInterp = isStatic ? 1.0f : 0.0f;
    _staticT = 0.0f;
    _staticFadeDuration = duration;
    _fadingMode = isStatic ? 1 : 2;
}

void Boss2Head::setFollowTarget(Transform* target) {
    _followTarget = target;
}

void Boss2Head::setTargetFollowPower(const Vector2& power) {
    _followPower.set(power);
}

void Boss2Head::setRestingPos(const Vector2& position, const bool instant) {
    _restingPos.set(position);
    if (instant && _followTarget == nullptr) {
        _transform->setPosition(position, true);
    }
}

void Boss2Head::setLookAt(const bool lookAtTarg) {
    _lookAtTarget = lookAtTarg;
}

void Boss2Head::setMinMaxPos(const Vector2& min, const Vector2& max) {
    _minPos.set(min);
    _maxPos.set(max);
}

void Boss2Head::setTargetOffset(const Vector2& offset) {
    _offsetToTarget.set(offset);
}

void Boss2Head::handleStaticInterp(const float delta) {
    switch (_fadingMode)
    {
    case 1:
        _staticT += delta;
        if (_staticT >= _staticFadeDuration) {
            _staticT = _staticFadeDuration;
            _staticInterp = 1.0f;
            _fadingMode = 0;
            return;
        }
        _staticInterp = _staticT / _staticFadeDuration;
        break;
    case 2:
        _staticT += delta;
        if (_staticT >= _staticFadeDuration) {
            _staticT = _staticFadeDuration;
            _staticInterp = 0.0f;
            _fadingMode = 0;
            return;
        }
        _staticInterp = 1.0f - _staticT / _staticFadeDuration;
        break;
    }

}
