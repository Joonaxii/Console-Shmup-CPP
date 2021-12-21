#include "../../Includes.h"
#include "SortingLayer.h"
#include "../Math/Math.h"

SortingLayer::SortingLayer() : orderInLayer(0), layerIndex(0) { }

SortingLayer::SortingLayer(const std::string layerName, const signed short order) : orderInLayer(clamp(order + MAXINT16, 0, MAXUINT16))
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


