#pragma once
#include "Vector2.h"

class Rect
{
public:

    Rect();
    Rect(const float centerX, const float centerY, const float width, const float height);
    Rect(const Vector2& min, const Vector2& max);
    ~Rect();

    const Vector2 getMin() const;
    const Vector2 getMax() const;

    const Vector2 getCenter() const;
    const Vector2 getSize() const;

    const bool containsPoint(const Vector2& point) const;
    const bool overlaps(const Rect& other) const;

    void setMinMax(const float minX, const float minY, const float maxX, const float maxY);
    void setMinMax(const Vector2& min, const Vector2& max);

    void set(const float centerX, const float centerY, const float width, const float height);
    void set(const Vector2& center, const Vector2& size);

private:

    Vector2 _min;
    Vector2 _max;

    Vector2 _size;
    Vector2 _center;
};

