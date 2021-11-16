#include "../../Includes.h"
#include "windows.h"

SpriteRenderer::SpriteRenderer() : _sprite(nullptr), layer(), _isActive(true) {
	_rendering = Engine::getInstance()->getRendering();
	_rendering->registerRenderer(this);
}

SpriteRenderer::~SpriteRenderer() {
	_sprite = nullptr;
}

void SpriteRenderer::setTransform(Transform* transform) {
	_transform = transform;
}

void SpriteRenderer::setLayer(const std::string layer) {
	this->layer.layerIndex = _rendering->layerNameToIndex(layer);
}

void SpriteRenderer::setSortingOrder(const unsigned short order) {
	this->layer.orderInLayer = order;
}

void SpriteRenderer::draw(char* buffer, unsigned int* depthBuffer) {
	if (_sprite == nullptr || _transform == nullptr) { return; }
	unsigned int un = layer.getUnion();
	_sprite->draw(_transform, buffer, depthBuffer, un, Rendering::CHAR_W, Rendering::GAME_AREA_H, Rendering::GAME_AREA_Y, false, false);
}

void SpriteRenderer::setActive(const bool active) {
	_isActive = active;
}

void SpriteRenderer::setSprite(Sprite* sprite) {
	_sprite = sprite;
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


