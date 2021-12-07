#include "AnimationFrame.h"

AnimationFrame::AnimationFrame() : _sprite(nullptr), _duration(0.0f) { }
AnimationFrame::AnimationFrame(AnimationFrame& frame) : _sprite(frame._sprite), _duration(frame._duration) { }
AnimationFrame::AnimationFrame(Sprite* sprt, const float duration) : _sprite(sprt), _duration(duration) { }
AnimationFrame::~AnimationFrame() { _sprite = nullptr; }

const float AnimationFrame::getDuration() const {
    return _duration;
}

const Sprite* AnimationFrame::getSprite() const {
    return _sprite;
}


