#include "Matrix3x3.h"
#include <math.h>
#include "Math.h"

//////////////---/////////////////
// m0 m1 m2 //   // m00 m01 m02 //
//          //   //             //
// m3 m4 m5 //   // m10 m11 m12 //
//          //   //             //
// m6 m7 m8 //   // m20 m21 m22 //
//////////////---/////////////////
const Matrix3x3 Matrix3x3::zero = Matrix3x3(0, 0, 0, 0, 0, 0, 0, 0, 0);
const Matrix3x3 Matrix3x3::identity = Matrix3x3(1, 0, 0, 0, 1, 0, 0, 0, 1);

Matrix3x3::Matrix3x3() : _m{0} { }

Matrix3x3::Matrix3x3(const Matrix3x3& mat) : _m{0} {
    memcpy(_m, mat._m, 9 * sizeof(float));
}

Matrix3x3::Matrix3x3(const float m00, const float m01, const float m02, 
                     const float m10, const float m11, const float m12, 
                     const float m20, const float m21, const float m22) : _m { m00, m01, m02, m10, m11, m12, m20, m21, m22} { }

Matrix3x3::~Matrix3x3()
{
}

void Matrix3x3::setPosition(const Vector2& positon) {
    _m[6] = positon.x;
    _m[7] = positon.y;
}

void Matrix3x3::setRotation(const float& rotation) {

    const float rads = rotation * DEG_2_RAD;
    _m[1] = cosf(rads);
    _m[4] = sinf(rads);

    _m[2] = -_m[4];
    _m[5] = _m[1];

    _m[8] = rotation;
}

void Matrix3x3::setScale(const Vector2& scale) {
    _m[0] = scale.x;
    _m[3] = scale.y;
}

const Matrix3x3 Matrix3x3::transpose() const {
    return Matrix3x3(_m[0], _m[3], _m[6], 
                     _m[1], _m[4], _m[7], 
                     _m[2], _m[5], _m[8]);
}

const Vector2 Matrix3x3::multiplyPoint(const Vector2& point) const {
    const float pX = point.x * _m[0];
    const float pY = point.y * _m[3];

    return Vector2((pX * _m[1] + pY * _m[2]) + _m[6],
                   (pY * _m[5] + pX * _m[4]) + _m[7]);
}

const Vector2 Matrix3x3::movePoint(const Vector2& point) const {
    return Vector2((point.x * _m[1] + point.y * _m[2]) + _m[6],
                   (point.y * _m[5] + point.x * _m[4]) + _m[7]);
}

const Vector2 Matrix3x3::rotatePointRev(const Vector2& point) const {
    return Vector2((point.x * _m[1] + point.y * _m[2]),
                   (point.y * _m[5] + point.x * _m[4]));
}

const Vector2 Matrix3x3::multiplyVector(const Vector2& vector) const {
    const float pX = vector.x * _m[0];
    const float pY = vector.y * _m[3];

    return Vector2((pX *_m[1] + pY * _m[2]), (pY * _m[5] + pX * _m[4]));
}

const Vector2 Matrix3x3::multiplyAbsVector(const Vector2& vector) const {
    const float pX = vector.x * _m[0];
    const float pY = vector.y * _m[3];

    return Vector2((pX * abs(_m[1]) + pY * abs(_m[2])), (pY * abs(_m[5]) + pX * abs(_m[4])));
}

const Vector2 Matrix3x3::scaleVector(const Vector2& vector) const {
    return Vector2(vector.x * _m[0], vector.y * _m[3]);
}

const float Matrix3x3::rotate(const float rotation) const {
    return rotation + _m[8];
}

const Matrix3x3 Matrix3x3::inverse() const {
    float det = determinant();
    if (det == 0) { return Matrix3x3(zero); }

    Matrix3x3 tr = transpose();
    const float detOne = 1.0f / det;
  
    const float a =  tr.det2x2(4, 5, 7, 8) * detOne; //Scale:  X
    const float b = -tr.det2x2(3, 5, 6, 8) * detOne; //Rot A:  Cos(a)
    const float c =  tr.det2x2(3, 4, 6, 7) * detOne; //Rot B: -Sin(a)

    const float d = -tr.det2x2(1, 2, 7, 8) * detOne; //Scale:  Y
    const float e =  tr.det2x2(0, 2, 6, 8) * detOne; //Rot C:  Sin(a)
    const float f = -tr.det2x2(0, 1, 6, 7) * detOne; //Rot D:  Cos(a)

    const float g =  tr.det2x2(1, 2, 4, 5) * detOne; //Pos:    X
    const float h = -tr.det2x2(0, 2, 3, 5) * detOne; //Pos:    Y
    const float i =  tr.det2x2(0, 1, 3, 4) * detOne; //Rot E:  Angles

    return Matrix3x3(a, b , c, d, e, f, g, h, i);
}

const Vector2 Matrix3x3::inversePosition() const {
    float det = determinant();
    if (det == 0) { return Vector2(0, 0); }

    Matrix3x3 tr = transpose();
    const float detOne = 1.0f / det;
    return Vector2(tr.det2x2(1, 2, 4, 5) * detOne, -tr.det2x2(0, 2, 3, 5) * detOne);
}

const float Matrix3x3::inverseRotation() const {
    float det = determinant();
    if (det == 0) { return 0; }

    Matrix3x3 tr = transpose();
    const float detOne = 1.0f / det;
    return tr.det2x2(0, 1, 3, 4) * detOne;
}

const Vector2 Matrix3x3::inverseScale() const {
    float det = determinant();
    if (det == 0) { return Vector2(0, 0); }

    Matrix3x3 tr = transpose();
    const float detOne = 1.0f / det;
    return Vector2(tr.det2x2(4, 5, 7, 8) * detOne, -tr.det2x2(1, 2, 7, 8) * detOne);
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

const float Matrix3x3::determinant() const {
    return (_m[0] * det2x2(4, 8, 5, 7)) -
           (_m[1] * det2x2(3, 8, 5, 6)) +
           (_m[2] * det2x2(3, 5, 4, 6));
}

const float Matrix3x3::det2x2(const int a, const int b, const int c, const int d) const {
    return (_m[a] * _m[b]) - (_m[c] * _m[d]);
}
