#include "Math.h"

int clamp(const int value, const int minV, const int maxV) {
    return value < minV ? minV : value > maxV ? maxV : value;
}

float clamp(const float value, const float minV, const float maxV) {
    return value < minV ? minV : value > maxV ? maxV : value;
}