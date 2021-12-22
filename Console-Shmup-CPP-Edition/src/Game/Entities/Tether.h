#pragma once
#include "../../Engine/Math/Vector2.h"
#include "../../Engine/Components/Transform.h"
#include "../../Engine/Math/WaveSpecifications.h"
#include "GenericEntity.h"

class Transform;
class GenericEntity;
class Tether
{
public:

    Tether();
    Tether(const int tetherSize, const float speedGlobal, const float speedSeg, const float startSize, const float endSize, const WaveSpecifications& wave, const float bendPower, const float bendPowerMaxDist);
    ~Tether();

    void setSprite(Sprite* sprite, const std::string layer, const short startOrder);
    void setPoint(Transform* tr, const Vector2& offset, const bool isA);
    void update(const float delta);

private:

    const WaveSpecifications _wave;
    const float _bendPower;
    const float _bendDist;

    const float _globalTimeSpeed;
    const float _segTimeSpeed;

    float _timeGlobal;
    float _timeSeg;

    const int _tetherSize;
    GenericEntity** _tetherObjs;

    Vector2 _offsetA;
    Transform* _pointA;

    Vector2 _offsetB;
    Transform* _pointB;
};

