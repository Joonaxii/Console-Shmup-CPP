#pragma once
#include <string>

class SortingLayer
{
public:

    SortingLayer();
    SortingLayer(const std::string layerName, const unsigned short order);
    ~SortingLayer();

    signed short orderInLayer;
    unsigned short layerIndex;

    const unsigned int getUnion() const;

    const bool operator<(const SortingLayer& other) const;
    const bool operator>(const SortingLayer& other) const;

    const bool operator==(const SortingLayer& other) const;
    const bool operator!=(const SortingLayer& other) const;

};

