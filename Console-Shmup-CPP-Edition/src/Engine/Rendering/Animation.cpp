#include "Animation.h"
#include "AnimationFrame.h"
#include "../Math/Math.h"

Animation::Animation(AnimationFrame* frames, const int frameCount, const bool loop) : _totalDuration(0), _loop(loop) {

    _frames = new AnimationFrame*[frameCount];
	_totalDuration = 0;
	for (size_t i = 0; i < frameCount; i++) {
		auto frm = frames[i];
		_frames[i] = new AnimationFrame(frm);
		_totalDuration += frm.getDuration();
	}
	_frameCount = frameCount;
}

Animation::~Animation() {
	delete[] _frames;
}

const float Animation::getTotalDuration() const {
	return _totalDuration;
}

const int Animation::getFrameCount() const {
	return _frameCount;
}

const AnimationFrame* Animation::getFrame(const int index) const {
	if (index < 0 || index >= _frameCount) { return nullptr; }
	return _frames[index];
}

const bool Animation::evaluateFrame(const float time, int* frameIndex, AnimationFrame** frame) const {

	if (!_loop && time >= _totalDuration) {

		*frameIndex = _frameCount - 1;
		*frame = _frames[*frameIndex];
		return true;
	}

	const float nT = repeat(time, _totalDuration);

	float acc = 0;
	for (size_t i = 0; i < _frameCount; i++)
	{
		auto frm = _frames[i];
		acc += frm->getDuration();

		if (acc >= nT) {
			*frameIndex = i;
			*frame = frm;
			break;
		}
	}
	return false;
}
