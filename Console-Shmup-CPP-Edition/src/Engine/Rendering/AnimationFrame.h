#pragma once
#include "Sprite.h"

class AnimationFrame
{
public:
    AnimationFrame();
    AnimationFrame(AnimationFrame& frame);
    AnimationFrame(Sprite* sprt, const float duration);
    ~AnimationFrame();

    const float getDuration() const;
    const AnimationFrame& getSprite() const;

private:
    float _duration;
    Sprite* _sprite;
};

