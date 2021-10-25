#pragma once
#include <string>
class Vector2Int
{
public:
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

