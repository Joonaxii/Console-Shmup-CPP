#include "../../Includes.h"
#include "windows.h"
#include "SpriteFactory.h"

bool SpriteRenderer::DRAW_BOUNDS = false;

SpriteRenderer::SpriteRenderer() : _sprite(nullptr), _boundSprite(nullptr), layer(), _debugLayer("Debug", 0), _isActive(true), _bounds(), _transform(nullptr), _constraints() {
	_rendering = Engine::getInstance()->getRendering();
	_rendering->registerRenderer(this);
}

SpriteRenderer::~SpriteRenderer() {
	_sprite = nullptr;
	_boundSprite = nullptr;
	_transform = nullptr;
}

void SpriteRenderer::setTransform(Transform* transform) {
	_transform = transform;
}

void SpriteRenderer::setLayer(const std::string layer) {
	this->layer.layerIndex = _rendering->layerNameToIndex(layer);
}

void SpriteRenderer::setSortingOrder(const unsigned short order) {
	this->layer.orderInLayer = order;
	this->_debugLayer.orderInLayer = order;
}

void SpriteRenderer::draw(char* buffer, unsigned int* depthBuffer) {
	if (_sprite == nullptr || _transform == nullptr) { return; }

	const auto mat = _transform->getMatrix(true);

	const auto sprtB = _sprite->getBounds();
	const auto sprtCenter = mat.multiplyPoint(sprtB.getCenter());
    auto sprtBS = mat.multiplyAbsVector(sprtB.getSize());

	sprtBS.set(abs(sprtBS.x), abs(sprtBS.y));

	_bounds.set(sprtCenter, sprtBS);
	if (!_bounds.overlaps(Rendering::GAME_AREA_BOUNDS)) { return; }

	if (DRAW_BOUNDS) {
		
		_boundSprite = SpriteFactory::getBox(sprtBS.x, sprtBS.y);
		if (_boundSprite != nullptr) {
			unsigned int debugUN = _debugLayer.getUnion();
			_boundSprite->draw(sprtCenter, buffer, depthBuffer, debugUN, Rendering::CHAR_W, Rendering::GAME_AREA_H, Rendering::GAME_AREA_Y, false, false);
		}
	}

	unsigned int un = layer.getUnion();
	_sprite->draw(_transform, buffer, depthBuffer, un, Rendering::CHAR_W, Rendering::GAME_AREA_H, Rendering::GAME_AREA_Y, false, false);
}

const Rect SpriteRenderer::getBounds() const {
	return _bounds;
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


