#pragma once
#include "../Enemy.h"
#include "../../Tether.h"

class Boss2Head : public Enemy {

public:
    Boss2Head();
    Boss2Head(const short baseSortingOrder, const float direction, const float phaseOffset, Transform* target, const int maxHP);
    ~Boss2Head();

    const short getRenderDepth() const;

    bool update(const float delta);

    void setFollowPower(const Vector2& power);
    void setRotationPower(const float power);

    void setFollowSpeed(const float speed);
    void setRotationSpeed(const float speed);

    void setStatic(const bool isStatic, const float duration);

    void setFollowTarget(Transform* target);
    void setTargetFollowPower(const Vector2& power);
    void setRestingPos(const Vector2& position, const bool instant);

    void setLookAt(const bool lookAtTarg);

    void setMinMaxPos(const Vector2& min, const Vector2& max);
    void setTargetOffset(const Vector2& offset);

private: 
    const float _timeOffset;
    const float _direction;

    short _renderDepth;
    Transform* _followTarget;

    Vector2 _restingPos;

    GenericEntity* _fangA;
    GenericEntity* _fangB;

    Transform* _targetB;
    Tether* _neck;

    float _followSpeed;
    float _rotationSpeed;

    Vector2 _velocity;

    int _fadingMode;
    float _staticFadeDuration;
    float _staticInterp;
    float _staticT;

    bool _lookAtTarget;

    Vector2 _followPower;
    float _rotatePower;

    Vector2 _maxPos;
    Vector2 _minPos;

    Vector2 _offsetToTarget;
    Vector2 _followVelo;
    float _rotateVelo;

    void handleStaticInterp(const float delta);
};

