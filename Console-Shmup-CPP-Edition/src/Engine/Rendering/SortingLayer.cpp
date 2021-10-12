#include "../../Includes.h"
#include "SortingLayer.h"

SortingLayer::SortingLayer() : orderInLayer(0), layerIndex(0) { }

SortingLayer::SortingLayer(const std::string layerName, const unsigned short order) : orderInLayer(order)
{
    Rendering* rend = Engine::getInstance()->getRendering();
    layerIndex = rend->layerNameToIndex(layerName);   
}

SortingLayer::~SortingLayer() { }

const unsigned int SortingLayer::getUnion() const {
    return (unsigned int)orderInLayer + (unsigned int)(layerIndex << 16);
}

const bool SortingLayer::operator<(const SortingLayer& other) const  {
    return layerIndex <= other.layerIndex && orderInLayer < other.layerIndex;
}

const bool SortingLayer::operator>(const SortingLayer& other) const  {
    return layerIndex >= other.layerIndex && orderInLayer > other.layerIndex;
}

const bool SortingLayer::operator==(const SortingLayer& other) const  {
    return layerIndex == other.layerIndex && orderInLayer == other.layerIndex;
}

const bool SortingLayer::operator!=(const SortingLayer& other) const  {
    return !(this == &other);
}


