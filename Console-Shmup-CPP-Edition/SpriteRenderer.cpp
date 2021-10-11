#include "Includes.h"
#include "windows.h"

SpriteRenderer::SpriteRenderer() :_position(0, 0), positionGrid(0, 0), _sprite(nullptr), layer(), _isActive(true) {
	_rendering = Engine::getInstance()->getRendering();
	_rendering->registerRenderer(this);
}

SpriteRenderer::~SpriteRenderer() {
	_sprite = nullptr;
}

void SpriteRenderer::setLayer(const std::string layer) {
	this->layer.layerIndex = _rendering->layerNameToIndex(layer);
}

void SpriteRenderer::setPosition(const Vector2& position) {

	_position.x = position.x;
	_position.y = -position.y;

	if (_sprite == nullptr) { return; }

	positionGrid.x = (int)(_position.x + _sprite->pivot.x) + Rendering::CHAR_W / 2;
	positionGrid.y = (int)(_position.y + _sprite->pivot.y) + Rendering::GAME_AREA_H / 2;
}

void SpriteRenderer::setActive(const bool active) {
	_isActive = active;
}

void SpriteRenderer::setSprite(Sprite* sprite) {
	_sprite = sprite;
	setPosition(_position);
}

const bool SpriteRenderer::canRender() const {
	return _isActive && _sprite != nullptr;
}

const bool SpriteRenderer::operator<(const SpriteRenderer& other) const {
	return layer < other.layer;
}

const bool SpriteRenderer::operator>(const SpriteRenderer& other) const {
	return layer > other.layer;
}

Sprite* SpriteRenderer::getSprite() {
	return _sprite;
}


