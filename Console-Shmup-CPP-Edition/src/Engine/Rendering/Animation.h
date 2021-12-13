#pragma once
#include "Sprite.h"

class AnimationFrame;
class Animation
{
public:
    Animation(AnimationFrame* frames, const int frameCount, const bool loop);
    ~Animation();

    const float getTotalDuration() const;
    const int getFrameCount() const;
    const AnimationFrame* getFrame(const int index) const;

    const bool evaluateFrame(const float time, int* frameIndex, AnimationFrame** frame) const;

private:
    AnimationFrame** _frames;
    int _frameCount;
    float _totalDuration;
    bool _loop;
};

