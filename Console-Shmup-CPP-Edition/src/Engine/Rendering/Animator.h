#pragma once
#include "Animation.h"
class Animator
{
public:

    void setSpeed(const float speed);
    const float getSpeed() const;

    void addAnimation(Animation* anim);
    void removeAnimation(Animation* anim);

private: 
    float _speed;

    std::vector<Animation*> _animations;
};

