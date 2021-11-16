#include "Matrix3x3.h"
#include <math.h>
#include "Math.h"

//////////////  /////////////////
// m0 m1 m2 //  // m00 m01 m02 //
//          //  //             //
// m3 m4 m5 //  // m10 m11 m12 //
//          //  //             //
// m6 m7 m8 //  // m20 m21 m22 //
//////////////  /////////////////

Matrix3x3::Matrix3x3() : _m{0} { }

Matrix3x3::Matrix3x3(const Matrix3x3& mat) : _m{0} {
    memcpy(_m, mat._m, 9 * sizeof(float));
}

Matrix3x3::Matrix3x3(const float m00, const float m01, const float m02, 
                     const float m10, const float m11, const float m12, 
                     const float m20, const float m21, const float m22) : _m { m00, m01, m02, m10, m11, m12, m20, m21, m22} { }

void Matrix3x3::setPosition(const Vector2& positon) {
    _m[6] = positon.x;
    _m[7] = positon.y;
}

void Matrix3x3::setRotation(const float& rotation) {

    const float rads = rotation * DEG_2_RAD;
    _m[1] = cosf(rads);
    _m[5] = sinf(rads);

    _m[2] = -_m[5];
    _m[6] = _m[1];

    _m[8] = rotation;
}

void Matrix3x3::setScale(const Vector2& scale) {
    _m[0] = scale.x;
    _m[3] = scale.y;
}

Matrix3x3 Matrix3x3::transpose()
{
    return Matrix3x3(_m[0], _m[3], _m[6], 
                     _m[1], _m[4], _m[7], 
                     _m[2], _m[5], _m[8]);
}

Vector2 Matrix3x3::multiplyPoint(const Vector2& point) {
    return Vector2((point.x * _m[1] + point.y * _m[2]) * _m[0] + _m[6], (point.y * _m[5] + point.x * _m[4]) * _m[3] + _m[7]);
}

Vector2 Matrix3x3::multiplyVector(const Vector2& vector) {
    return Vector2((vector.x * _m[1] + vector.y * _m[2]) * _m[0], (vector.y * _m[5] + vector.x * _m[4]) * _m[3]);
}

Vector2 Matrix3x3::scaleVector(const Vector2& vector) {
    return Vector2(vector.x * _m[0], vector.y * _m[3]);
}

float Matrix3x3::rotate(const float rotation) {
    return rotation + _m[8];
}

Matrix3x3 Matrix3x3::fromTRS(const Vector2 position, const float zRotation, const Vector2 scale) {
    return Matrix3x3().TRS(position, zRotation, scale);
}

Matrix3x3 Matrix3x3::TRS(const Vector2 position, const float zRotation, const Vector2 scale) {
    setPosition(position);
    setRotation(zRotation);
    setScale(scale);
    return *this;
}
