#include "Vector2.h"
#include "sstream"
#include "string"

Vector2::Vector2() : x(0), y(0) {}
Vector2::Vector2(float x, float y) : x(x), y(y) {}
Vector2::~Vector2() {}

Vector2 Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2 Vector2::operator-=(const Vector2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2 Vector2::operator-() {
   
    return Vector2(-x, -y);
}

std::string Vector2::toString()
{
    std::ostringstream str;
    str << "(" << x << "," << y << ")";
    return str.str();
}
