#pragma once
#include "CollisionGridNode.h"
#include "CollisionSystem.h"
#include "Collider2D.h"

class Collider2D;
class CollisionGrid
{

public:
    static const int GRID_WIDTH         = 48;
    static const int GRID_HEIGHT        = 48;
    static const int GRID_RESOULTION    = GRID_WIDTH * GRID_HEIGHT;
    static const int CHUNK_COUNT        = GRID_RESOULTION / 64.0f;

    CollisionGrid();
    ~CollisionGrid();

    void addCollider(Collider2D* collider);
    void clear();

private:
    CollisionGridNode _nodes[GRID_RESOULTION];
    std::vector<Collider2D*> _colliders;
};

