#include "Animator.h"
#include "AnimationFrame.h"
#include <algorithm>

Animator::Animator(SpriteRenderer* renderer) : Animator(renderer, 1.0f) { }
Animator::Animator(SpriteRenderer* renderer, const float speed) : _renderer(renderer), _speed(speed), _animations(), _currentFrameIndex(0), _currentAnimIndex(0), _currentAnim(nullptr) { }
Animator::~Animator() { }

void Animator::setSpeed(const float speed) {
	_speed = speed;
}

const float Animator::getSpeed() const {
	return _speed;
}

const bool Animator::isPlaying() const {
	return _isPlaying;
}

void Animator::setRenderer(SpriteRenderer* renderer) {
	_renderer = renderer;
}

void Animator::addAnimation(Animation* anim) {
	_animations.push_back(anim);
}

bool Animator::removeAnimationAt(const int index) {
	if (index < 0 || index >= _animations.size()) { return false; }
	_animations.erase(_animations.begin() + index);
	return true;
}

bool Animator::removeAnimation(Animation* anim) {
	auto it = _animations.erase(std::remove(_animations.begin(), _animations.end(), anim), _animations.end());
	return it != _animations.end();
}

void Animator::play() {
	_currentFrameIndex = 0;
	_isPlaying = true;
}

bool Animator::play(Animation* anim) {
	if (_renderer == nullptr || anim == nullptr) { return false; }
	_currentAnim = anim;

	auto frm = _currentAnim->getFrame(0);
	_renderer->setSprite(frm->getSprite());
	
	play();
}

bool Animator::play(const int index) {
	if (_renderer == nullptr || index < 0 || index >= _animations.size()) { return false; }
	_currentAnim = _animations[index];
	_currentAnimIndex = index;

	auto frm = _currentAnim->getFrame(0);
	_renderer->setSprite(frm->getSprite());
	play();
}

void Animator::stop(const bool resetTime) {
	_isPlaying = false;
	if (resetTime) {
		_time = 0;
	}
}

void Animator::update(const float delta) {
	if (!_isPlaying || _currentAnim == nullptr || _renderer == nullptr) { return; }

	_time += delta * _speed;

	AnimationFrame* frame(nullptr);
	int frameNum(-1);
	if (_currentAnim->evaluateFrame(_time, &frameNum, &frame)) {
		
	
		stop(true);
		return;
	}

	if (_currentFrameIndex != frameNum && frameNum >= 0) {
		_currentFrameIndex = frameNum;
		_renderer->setSprite(frame->getSprite());
	}
}
