#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

const float DEG_2_RAD = (M_PI / 180.0f);
const float RAD_2_DEG = (180.0f / M_PI);

int clamp(const int value, const int minV, const int maxV);
float clamp(const float value, const float minV, const float maxV);

//int min(const int value, const int minV);
//int max(const int value, const int maxV);