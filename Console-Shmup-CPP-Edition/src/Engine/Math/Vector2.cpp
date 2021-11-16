#include "Vector2.h"
#include "sstream"
#include "string"
#include "Math.h"
#include <math.h>

const Vector2 Vector2::up = Vector2(0, 1);
const Vector2 Vector2::down = Vector2(0, -1);

const Vector2 Vector2::right = Vector2(1, 0);
const Vector2 Vector2::left = Vector2(-1, 0);

const Vector2 Vector2::zero = Vector2(0, 0);
const Vector2 Vector2::one = Vector2(1, 1);

Vector2::Vector2() : x(0), y(0) {}
Vector2::Vector2(float x, float y) : x(x), y(y) {}
Vector2::~Vector2() {}

const float Vector2::angleDegrees(const Vector2& ref, const bool isSigned) const {
	return angleRadians(ref, isSigned) * RAD_2_DEG;
}

const float Vector2::angleRadians(const Vector2& ref, const bool isSigned) const {

	float sqr = sqrtf(sqrMagnitude() * ref.sqrMagnitude());
	if (sqr < FLT_EPSILON) { return 0.0f; }
	return isSigned ? acosf(clamp(dot(*this, ref) / sqr, -1.0f, 1.0f)) * sign(x * ref.x - y * ref.y) : acosf(clamp(dot(*this, ref) / sqr, -1.0f, 1.0f));
}

const Vector2 Vector2::operator+(const Vector2& a) const {
	return Vector2(x + a.x, y + a.y);
}

const Vector2 Vector2::operator-(const Vector2& a) const {
	return Vector2(x - a.x, y - a.y);
}

const float Vector2::magnitude()const {
	return sqrtf(sqrMagnitude());
}

const float Vector2::sqrMagnitude()const {
	return x * x + y * y;
}

Vector2 Vector2::operator+=(const Vector2& other) {
	x += other.x;
	y += other.y;
	return *this;
}

Vector2 Vector2::normalize() {
	if (x == 0 && y == 0) { return *this; }
	const float mag = magnitude();
	x /= mag;
	y /= mag;
	return *this;
}

const Vector2 Vector2::getNormalized() const {
	return Vector2(x, y).normalize();
}

Vector2 Vector2::operator-=(const Vector2& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

const bool Vector2::operator==(const Vector2& other) const {
	return x == other.x && y == other.y;
}

const Vector2 Vector2::lerp(const Vector2& lhs, const Vector2& rhs, const float t) {
	return Vector2(lhs.x + (rhs.x - lhs.x) * t, lhs.y + (rhs.y - lhs.y) * t);
}

const float Vector2::dot(const Vector2& lhs, const Vector2& rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

const bool Vector2::operator!=(const Vector2& other) const {
	return x != other.x && y != other.y;
}

const Vector2 Vector2::operator-() const {
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
