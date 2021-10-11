#pragma once
#include <string>

class Vector2
{

public:
    float x;
    float y;

    Vector2();
    Vector2(float x, float y);
    ~Vector2();

    std::string toString();
};

