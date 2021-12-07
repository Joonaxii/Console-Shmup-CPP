#include "Animation.h"

Animation::Animation(AnimationFrame* frames, const int frameCount) : _totalDuration(0) {

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
