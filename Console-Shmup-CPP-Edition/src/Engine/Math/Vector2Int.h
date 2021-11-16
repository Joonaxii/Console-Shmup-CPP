#pragma once
#include <functional>
#include <string>

class Vector2Int
{
public:

    struct hasher {
        size_t operator()(const Vector2Int& v) {
            return ((std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1)));
        }
    };

    int x;
    int y;

    Vector2Int();
    Vector2Int(int x, int y);
    ~Vector2Int();

    Vector2Int operator+=(const Vector2Int& other);
    Vector2Int operator-=(const Vector2Int& other);

    bool operator==(const Vector2Int& other);
    bool operator!=(const Vector2Int& other);

    Vector2Int operator-();

    void set(const Vector2Int& v);
    void set(const int x, const int y);

    std::string toString();
};

