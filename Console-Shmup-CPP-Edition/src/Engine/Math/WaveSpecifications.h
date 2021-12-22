#pragma once
#include "WaveType.h"
#include <math.h>

struct WaveSpecifications {
public:
    WaveSpecifications() : WaveSpecifications(WaveType::Sine, 0.0f, 1.0f, 1.0f){}
    WaveSpecifications(const WaveType type, const float phaseOffset, const float amplitude, const float frequency) : _type(type), _phaseOffset(phaseOffset), _amplitude(amplitude), _frequency(frequency) { }
    ~WaveSpecifications() {}

    const float getValue(const float time, const float offset) const {
        switch (_type)
        {
            default: return sinf(time * _frequency + _phaseOffset + offset) * _amplitude;
            case WaveType::Cosine: return cosf(time * _frequency + _phaseOffset + offset) * _amplitude;
        }
    }

private:
    const float _amplitude;
    const float _frequency;
    const float _phaseOffset;
    const WaveType _type;
};