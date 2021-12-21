#pragma once
#include "../Rendering.h"
#include "../SpriteRenderer.h"
#include "../TextRegion.h"

class UIElement
{
public:
    UIElement();
    UIElement(unsigned short order);
    ~UIElement();

    const bool getIsActive() const;
    void toggle(const bool toggle);
    SpriteRenderer* getRenderer();
    void drawTextRegions(char* buffer, unsigned int* depthBuffer);

    TextRegion& addRegion(const TextRegion& region);
    TextRegion& getRegion(const int i) const;
    const bool removeRegionAt(const int i);

private:
    bool _isActive;
    Transform* _transform;
    SpriteRenderer* _renderer;
    std::vector<TextRegion> _regions;
};

