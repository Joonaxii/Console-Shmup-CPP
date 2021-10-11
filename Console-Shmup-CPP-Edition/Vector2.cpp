#include "Vector2.h"
#include "sstream"
#include "string"

Vector2::Vector2() : x(0), y(0) {}
Vector2::Vector2(float x, float y) : x(x), y(y) {}
Vector2::~Vector2() {}

std::string Vector2::toString()
{
    std::ostringstream str;
    str << "(" << x << "," << y << ")";
    return str.str();
}
