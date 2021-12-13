#pragma once
enum class TransformConstraints
{
    None = 0,

    Position = 1,
    Rotation = 2,

    Scale = 4,
};

inline TransformConstraints operator |(TransformConstraints a, TransformConstraints b) {
    return (TransformConstraints)((int)a | (int)b);
}

inline TransformConstraints operator &(TransformConstraints a, TransformConstraints b) {
    return (TransformConstraints)((int)a & (int)b);
}