#pragma once
#include <string>

class SortingLayer
{
public:

    SortingLayer();
    SortingLayer(const std::string layerName, const unsigned short order);
    ~SortingLayer();

    unsigned short orderInLayer;
    unsigned int layerIndex;

    const bool operator<(const SortingLayer& other) const;
    const bool operator>(const SortingLayer& other) const;

    const bool operator==(const SortingLayer& other) const;
    const bool operator!=(const SortingLayer& other) const;
};

