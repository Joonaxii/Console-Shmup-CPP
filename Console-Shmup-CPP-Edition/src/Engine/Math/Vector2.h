#pragma once
#include <string>

class Vector2
{

public:
    static const Vector2 up;
    static const Vector2 down;
    static const Vector2 right;
    static const Vector2 left;

    static const Vector2 zero;
    static const Vector2 one;

    float x;
    float y;

    Vector2();
    Vector2(float x, float y);
    ~Vector2();

    const float angleDegrees(const Vector2& ref, const bool isSigned) const;
    const float angleRadians(const Vector2& ref, const bool isSigned) const;

    const float sqrMagnitude() const;
    const float magnitude() const;

    Vector2 normalize();
    const Vector2 getNormalized() const;

    Vector2 clampMagnitude(const float max);

    const static Vector2 smoothDamp(const Vector2& cur, const Vector2& target, Vector2* velocity, const float smoothTime, const float delta);

    const static Vector2 lerp(const Vector2& lhs, const Vector2& rhs, const float t);
    const static float cross(const Vector2& lhs, const Vector2& rhs);
    const static float dot(const Vector2& lhs, const Vector2& rhs);

    const static Vector2 rotate(const Vector2& input, const float radians);

    const Vector2 operator*(const Vector2& a) const;
    const Vector2 operator*(const float b) const;
    const Vector2 operator/(const float b) const;

    const Vector2 operator+(const Vector2& a) const;
    const Vector2 operator-(const Vector2& a) const;

    Vector2 operator+=(const Vector2& other);
    Vector2 operator-=(const Vector2& other);

    const bool operator==(const Vector2& other) const;
    const bool operator!=(const Vector2& other) const;

    const Vector2 operator-()const ;

    void set(const Vector2& v);
    void set(const float x, const float y);

    const std::string toString() const;
};

