#include "Time.h"
#include <chrono>

Time::Time() : _delta(0), _time(0), _frames(0), _fps(0), _prev(std::chrono::high_resolution_clock::now()){ }
Time::~Time() { }

float Time::getFramerate() {
    return _fps;
}

float Time::getDeltaTime() {
    return _delta;
}

float Time::getTime() {
    return _time;
}

long long Time::getFrames() {
    return _frames;
}

void Time::tick() {
    const auto now = std::chrono::high_resolution_clock::now();

    const auto elap = std::chrono::duration<float, std::milli>(now - _prev);
    _delta = elap.count() / 1000.0f;
    _time += _delta;

    _frames++;

    _fps = _frames / _time;
    _prev = now;
}
