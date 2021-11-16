#pragma once
#include "Vector2.h"

class Matrix3x3
{
public:

    static const Matrix3x3 identity;
    static const Matrix3x3 zero;

    Matrix3x3();
    Matrix3x3(const Matrix3x3& mat);
    Matrix3x3(const float m00, const float m01, const float m02, const float m10, const float m11, const float m12, const float m20, const float m21, const float m22);

    float const& operator[](int i) const {
        return i < 0 || i > 8 ? 0 : _m[i];
    }

    const float at(const int i);
    const float at(const int r, const int c);

    void setPosition(const Vector2& positon);
    void setRotation(const float& rotation);
    void setScale(const Vector2& scale);

    Matrix3x3 transpose();

    Vector2 multiplyPoint(const Vector2& point);
    Vector2 multiplyVector(const Vector2& vector);
    Vector2 scaleVector(const Vector2& vector);
    float rotate(const float rotation);

    static Matrix3x3 fromTRS(const Vector2 position, const float zRotation, const Vector2 scale);
    Matrix3x3 TRS(const Vector2 position, const float zRotation, const Vector2 scale);

private:

    float _m[9];



};

