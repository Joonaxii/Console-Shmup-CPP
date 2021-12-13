#include "Math.h"

const float sign(const float val) {
    return val >= 0 ? 1 : -1;
}

const float lerp(const float from, const float to, const float t) {
    return from + (to - from) * t;
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
