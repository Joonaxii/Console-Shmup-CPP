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

    Vector2 operator+=(const Vector2& other);
    Vector2 operator-=(const Vector2& other);

    bool operator==(const Vector2& other);
    bool operator!=(const Vector2& other);

    Vector2 operator-();

    std::string toString();
};

