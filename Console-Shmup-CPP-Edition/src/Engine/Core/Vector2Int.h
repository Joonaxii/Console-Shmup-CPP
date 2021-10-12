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

    std::string toString();
};

