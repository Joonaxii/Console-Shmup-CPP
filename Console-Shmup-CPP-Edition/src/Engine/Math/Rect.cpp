#include "Rect.h"
#include "../Collision/CollisionSystem.h"

Rect::Rect() : _center(0, 0), _min(0,0), _max(0,0), _size(0, 0) { }

Rect::Rect(const float centerX, const float centerY, const float width, const float height) {
    set(centerX, centerY, width, height);
}

Rect::Rect(const Vector2& min, const Vector2& max) {
    setMinMax(min, max);
}

Rect::~Rect() { }

const Vector2 Rect::getMin() const {
    return _min;
}

const Vector2 Rect::getMax() const {
    return _max;
}

const Vector2 Rect::getCenter() const {
    return _center;
}

const Vector2 Rect::getSize() const {
    return _size;
}

const bool Rect::containsPoint(const Vector2& point) const {
    return CollisionSystem::pointVsAABB(point, _min, _max);
}

const bool Rect::overlaps(const Rect& other) const {
    return  CollisionSystem::aabbVsAABB(_min, _max, other._min, other._max);
}

void Rect::setMinMax(const float minX, const float minY, const float maxX, const float maxY) {
    _min.set(minX, minY);
    _max.set(maxX, maxY);

    _size = (_max - _min);
    const auto extents = _size * 0.5f;
    _center.set(_min.x + extents.x, _min.y + extents.y);
}

void Rect::setMinMax(const Vector2& min, const Vector2& max) {
    setMinMax(min.x, min.y, max.x, max.y);
}

void Rect::set(const float centerX, const float centerY, const float width, const float height) {
    _center.set(centerX, centerY);

    _size.set(width, height);

    const Vector2 extents(width * 0.5f, height * 0.5f);
    _min.set(centerX - extents.x, centerY - extents.y);
    _max.set(centerX + extents.x, centerY + extents.y);
}

void Rect::set(const Vector2& center, const Vector2& size) {
    set(center.x, center.y, size.x, size.y);
}
