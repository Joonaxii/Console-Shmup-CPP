#pragma once
#include <chrono>

class Time
{
public:

    Time();
    ~Time();

    const float getFramerate()const ;
    const float getDeltaTime()const ;
    const float getTime()const ;
    const long long getFrames()const ;

    void tick();

private:
    float _delta;
    float _time;
    float _fps;
    long long _frames;

    std::chrono::steady_clock::time_point _prev;
};

