#include "Includes.h"

SpriteRenderer::SpriteRenderer() :_position(0, 0), positionGrid(0, 0), _sprite(nullptr), layer(), _isActive(true) { 
    _rendering = Engine::getInstance()->getRendering();
}

SpriteRenderer::~SpriteRenderer()  { 
    _sprite = nullptr;
}

void SpriteRenderer::setLayer(const std::string layer) {
    this->layer.layerIndex = _rendering->layerNameToIndex(layer);
}

void SpriteRenderer::setPosition(const Vector2& position) {
    if (_sprite == nullptr) { return; }

    positionGrid.x = (int)(position.x + _sprite->pivot.x);
    positionGrid.y = (int)(position.y + _sprite->pivot.y) + Rendering::GAME_AREA_START;

    _position.x = position.x;
    _position.y = position.y;
}

const bool SpriteRenderer::canRender() const {
    return _isActive && _sprite != nullptr;
}


