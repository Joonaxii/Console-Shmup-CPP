#pragma once
#include <vector>
#include "Collider2D.h"

#define ulong unsigned long long

class Colldier2D;
class CollisionGridNode
{
public:

    CollisionGridNode();
    CollisionGridNode(const ulong chunkBit, const int chunkID, const ulong localBit);
    ~CollisionGridNode();

   // bool insertBody(Collider2D* body);

    //Collider2D* getBodyAt(const int i);
    //const int getBodyCount() const;

private:
    ulong _chunkBit;
    int _chunkIndex;
    ulong _localBit;

    //std::vector<Collider2D*> _bodies;
};

