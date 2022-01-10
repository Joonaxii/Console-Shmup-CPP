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
	return isSigned ? -atan2f(dot(Vector2(-y, x), ref), dot(*this, ref)) : acosf(clamp(dot(*this, ref), -1.0f, 1.0f));
}

const Vector2 Vector2::operator*(const Vector2& a) const {
	return Vector2(x * a.x, y * a.y);
}

const Vector2 Vector2::operator*(const float s) const {
	return Vector2(x * s, y * s);
}

const Vector2 Vector2::operator/(const float b) const {
	return Vector2(x / b, y / b);
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

Vector2 Vector2::clampMagnitude(const float max) {
	const float mag = magnitude();

	if (mag > max) {
		x = (x / mag) * max;
		y = (y / mag) * max;
	}
	return *this;
}

const Vector2 Vector2::smoothDamp(const Vector2& cur, const Vector2& target, Vector2* velocity, const float smoothTime, const float deltaTime) {
	if (smoothTime <= 0.0f) { return Vector2(target); }

	const float omega = smoothTime * 0.5f;
	const float delta = omega * deltaTime;
	const float d = 1.0f / (1.0f + delta + 0.48f * delta * delta + 0.235f * delta * delta * delta);

	const float diffX = cur.x - target.x;
	const float diffY = cur.y - target.y;

	const float tgtX = cur.x - diffX;
	const float tgtY = cur.y - diffY;

	const float tempX = (velocity->x - omega * diffX) * deltaTime;
	const float tempY = (velocity->y - omega * diffY) * deltaTime;

	float outX = tgtX + (diffX + tempX) * d;
	float outY = tgtY + (diffY + tempY) * d;


	const float ogMinCurX = target.x - cur.x;
	const float ogMinCurY = target.y - cur.y;

	const float outMinX = outX - target.x;
	const float outMinY = outY - target.y;

	if ((ogMinCurX * outMinX + ogMinCurY * outMinY) > 0) {
		velocity->x = 0.0f;
		velocity->y = 0.0f;
		return Vector2(target.x, target.y);
	}

	velocity->x = (velocity->x - omega * tempX) * d;
	velocity->y = (velocity->y - omega * tempY) * d;
	return Vector2(outX, outY);
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

const float Vector2::cross(const Vector2& lhs, const Vector2& rhs) {
	return (lhs.x * rhs.y - lhs.y * rhs.x);
}

const float Vector2::dot(const Vector2& lhs, const Vector2& rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

const Vector2 Vector2::rotate(const Vector2& v, const float radians) {
	const float sin = sinf(radians);
	const float cos = cosf(radians);
	return Vector2(v.x * cos - v.y * sin, v.x * sin + v.y * cos);
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

const std::string Vector2::toString() const {
	std::ostringstream str;
	str << "(" << x << "," << y << ")";
	return str.str();
}
