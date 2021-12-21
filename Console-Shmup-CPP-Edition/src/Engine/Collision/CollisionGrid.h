#pragma once
#include "CollisionGridNode.h"
#include "CollisionSystem.h"
#include "CollisionGlobals.h"

class Collider2D;
class CollisionGrid
{

public:
    CollisionGrid();
    ~CollisionGrid();

    void addCollider(Collider2D* collider);
    void clear();

private:
   // CollisionGridNode _nodes[GRID_RESOULTION];
    std::vector<Collider2D*> _colliders;
};

