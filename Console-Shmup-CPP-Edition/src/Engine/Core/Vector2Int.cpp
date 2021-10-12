#include "Vector2Int.h"
#include "sstream"
#include "string"

Vector2Int::Vector2Int() : x(0), y(0) {}
Vector2Int::Vector2Int(int x, int y) : x(x), y(y) {}
Vector2Int::~Vector2Int() {}

std::string Vector2Int::toString()
{
    std::ostringstream str;
    str << "(" << x << "," << y << ")";
    return str.str();
}