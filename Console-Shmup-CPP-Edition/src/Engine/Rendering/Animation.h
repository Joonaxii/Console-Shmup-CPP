#pragma once
#include "Sprite.h"
#include "AnimationFrame.h"

class Animation
{
public:
    Animation(AnimationFrame* frames, const int frameCount);
    ~Animation();

    const float getTotalDuration() const;
    const int getFrameCount() const;
    const AnimationFrame* getFrame(const int index) const;

private:
    AnimationFrame** _frames;
    int _frameCount;
    float _totalDuration;

};

