#include "Vector2Int.h"
#include "sstream"
#include "string"

Vector2Int::Vector2Int() : x(0), y(0) {}
Vector2Int::Vector2Int(int x, int y) : x(x), y(y) {}
Vector2Int::~Vector2Int() {}

Vector2Int Vector2Int::operator+=(const Vector2Int& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2Int Vector2Int::operator-=(const Vector2Int& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

bool Vector2Int::operator==(const Vector2Int& other) {
    return x == other.x && y == other.y;
}

bool Vector2Int::operator!=(const Vector2Int& other) {
    return x != other.x && y != other.y;
}

Vector2Int Vector2Int::operator-() {
    return Vector2Int(-x, -y);
}

void Vector2Int::set(const Vector2Int& other) {
    x = other.x;
    y = other.y;
}

void Vector2Int::set(const int x, const int y) {
    this->x = x;
    this->y = y;
}

std::string Vector2Int::toString()
{
    std::ostringstream str;
    str << "(" << x << "," << y << ")";
    return str.str();
}
