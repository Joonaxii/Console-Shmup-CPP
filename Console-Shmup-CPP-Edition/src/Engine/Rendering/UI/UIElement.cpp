#include "UIElement.h"

UIElement::UIElement() : UIElement(0) { }

UIElement::UIElement(unsigned short order) : _isActive(true) {
    _renderer = new SpriteRenderer();
    _transform = new Transform();

    _renderer->setLayer("UI");
    _renderer->setSortingOrder(order);
    _renderer->setTransform(_transform);
    _renderer->setActive(_isActive);
   
}

UIElement::~UIElement() {
    delete _transform;
    delete _renderer;
}

const bool UIElement::getIsActive() const {
    return _isActive;
}

void UIElement::toggle(const bool toggle) {
    _isActive = toggle;
    _renderer->setActive(_isActive);
}

SpriteRenderer* UIElement::getRenderer() {
    return _renderer;
}

void UIElement::drawTextRegions(char* buffer, unsigned int* depthBuffer) {
    for (size_t i = 0; i < _regions.size(); i++) {
        _regions[i].writeToBuffer(buffer, depthBuffer, Rendering::CHAR_W);
    }
}

const bool UIElement::removeRegionAt(const int i) {
    if (i < 0 || i >= _regions.size()) { return false; }
    _regions.erase(_regions.begin() + i);
    return true;
}
