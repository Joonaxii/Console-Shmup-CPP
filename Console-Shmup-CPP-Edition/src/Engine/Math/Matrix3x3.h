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
    ~Matrix3x3();

    float const& operator[](int i) const {
        return i < 0 || i > 8 ? 0 : _m[i];
    }

    const float at(const int i);
    const float at(const int r, const int c);

    void setPosition(const Vector2& positon);
    void setRotation(const float& rotation);
    void setScale(const Vector2& scale);

    const Matrix3x3 transpose() const;

    const Vector2 multiplyPoint(const Vector2& point) const;
    const Vector2 movePoint(const Vector2& point) const;
    const Vector2 rotatePointRev(const Vector2& point) const;
    const Vector2 multiplyVector(const Vector2& vector) const;
    const Vector2 multiplyAbsVector(const Vector2& vector) const;
    const Vector2 scaleVector(const Vector2& vector) const;
    const float rotate(const float rotation) const;

    const Matrix3x3 inverse() const;

    const Vector2 inversePosition() const;
    const float inverseRotation() const;
    const Vector2 inverseScale() const;

    static Matrix3x3 fromTRS(const Vector2 position, const float zRotation, const Vector2 scale);
    Matrix3x3 TRS(const Vector2 position, const float zRotation, const Vector2 scale);

    const float determinant() const;

private:

    float _m[9];

    const float det2x2(const int a, const int b, const int c, const int d) const;

};

