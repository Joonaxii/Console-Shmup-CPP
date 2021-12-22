#include "Math.h"

const float sign(const float val) {
    return val >= 0 ? 1 : -1;
}

const float lerp(const float from, const float to, const float t) {
    return from + (to - from) * t;
}

const float lerpAngle(const float from, const float to, const float t) {
    float delta(repeat(to - from, 360.0f));
    if (delta > 180.0f) { delta -= 360.0f; }
    return from + delta * t;
}

const int clamp(const int value, const int minV, const int maxV) {
    return value < minV ? minV : value > maxV ? maxV : value;
}

const float clamp(const float value, const float minV, const float maxV) {
    return value < minV ? minV : value > maxV ? maxV : value;
}

const float repeat(const float value, const float length) {
    if (length == 0) { return 0.0f; }
    return value - (floor(value / length) * length);
}

const Vector2 quadraticBezierCurve(const Vector2 p0, const Vector2 p1, const Vector2 p2, const float t) {
    const float u = 1.0f - t;
    const float tt = t * t;
    const float uu = u * u;

    return p0 * uu + p1 * (2.0f * u * t) + p2 * tt;
}
