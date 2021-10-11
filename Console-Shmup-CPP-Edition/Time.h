#pragma once
#include <chrono>

class Time
{
public:

    Time();
    ~Time();

    float getFramerate();
    float getDeltaTime();
    float getTime();
    long long getFrames();

    void tick();

private:
    float _delta;
    float _time;
    float _fps;
    long long _frames;

    std::chrono::steady_clock::time_point _prev;
};

