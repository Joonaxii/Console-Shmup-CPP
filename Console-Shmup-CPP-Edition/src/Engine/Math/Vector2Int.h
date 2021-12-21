#pragma once
#include <functional>
#include <string>

class Vector2Int
{
public:

    struct hasher {
        const size_t operator()(const Vector2Int& v) const {
            return ((std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1)));
        }
    };

    signed int x;
    signed int y;

    Vector2Int();
    Vector2Int(signed int x, signed int y);
    ~Vector2Int();

    Vector2Int operator+=(const Vector2Int& other);
    Vector2Int operator-=(const Vector2Int& other);

    const bool operator==(const Vector2Int& other) const;
    const bool operator!=(const Vector2Int& other) const;

    Vector2Int operator-();

    void set(const Vector2Int& v);
    void set(const int x, const int y);

    const std::string toString() const;
};

