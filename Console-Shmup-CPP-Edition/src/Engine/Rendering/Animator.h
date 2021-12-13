#pragma once
#include "Animation.h"
class Animator
{
public:

    Animator(SpriteRenderer* renderer);
    Animator(SpriteRenderer* renderer, const float speed);
    ~Animator();

    void setSpeed(const float speed);
    const float getSpeed() const;
    const bool isPlaying() const;

    void setRenderer(SpriteRenderer* renderer);

    void addAnimation(Animation* anim);
    bool removeAnimationAt(const int index);
    bool removeAnimation(Animation* anim);

    void play();
    bool play(Animation* anim);
    bool play(const int index);

    void stop(const bool resetTime);

    void update(const float delta);

private: 

    SpriteRenderer* _renderer;

    float _speed;
    std::vector<Animation*> _animations;

    bool _isPlaying;
    float _time;

    signed int _currentFrameIndex;
    signed int _currentAnimIndex;
    Animation* _currentAnim;
};

