#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Vector2.h"

const float DEG_2_RAD = (M_PI / 180.0f);
const float RAD_2_DEG = (180.0f / M_PI);

const float sign(const float val);

const float lerp(const float from, const float to, const float t);
const float lerpAngle(const float from, const float to, const float t);

const int clamp(const int value, const int minV, const int maxV);
const float clamp(const float value, const float minV, const float maxV);

const float repeat(const float value, const float length);
const float smoothDamp(const float cur, const float target, float* velocity, const float smoothTime, const float deltaTime);

const Vector2 infinity(const float t);
const Vector2 quadraticBezierCurve(const Vector2 p0, const Vector2 p1, const Vector2 p2, const float t);