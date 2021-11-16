#include "Vector2.h"
#include "sstream"
#include "string"

Vector2::Vector2() : x(0), y(0) {}
Vector2::Vector2(float x, float y) : x(x), y(y) {}
Vector2::~Vector2() {}

Vector2 Vector2::operator+(const Vector2& a) {
    return Vector2(x + a.x, y + a.y);
}

Vector2 Vector2::operator-(const Vector2& a) {
    return Vector2(x - a.x, y - a.y);
}

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

bool Vector2::operator==(const Vector2& other) {
    return x == other.x && y == other.y;
}

bool Vector2::operator!=(const Vector2& other) {
    return x != other.x && y != other.y;
}

Vector2 Vector2::operator-() {   
    return Vector2(-x, -y);
}

void Vector2::set(const Vector2& other) {
    x = other.x;
    y = other.y;
}

void Vector2::set(const float x, const float y) {
    this->x = x;
    this->y = y;
}

std::string Vector2::toString() {
    std::ostringstream str;
    str << "(" << x << "," << y << ")";
    return str.str();
}
