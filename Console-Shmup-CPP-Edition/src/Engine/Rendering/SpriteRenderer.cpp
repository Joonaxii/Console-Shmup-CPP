#include "../../Includes.h"
#include "windows.h"
#include "SpriteFactory.h"
#include "../Math/Math.h"

bool SpriteRenderer::DRAW_BOUNDS = false;

SpriteRenderer::SpriteRenderer() : _flipX(false), _flipY(false), _sprite(nullptr), _boundSprite(nullptr), layer(), _debugLayer("Debug", 0), _isActive(true), _bounds(), _transform(nullptr), _constraints() {
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

void SpriteRenderer::setSortingOrder(const signed short order) {
	unsigned short uOrder = clamp(order + MAXINT16, 0, MAXUINT16);

	this->layer.orderInLayer = uOrder;
	this->_debugLayer.orderInLayer = uOrder;
}

const bool SpriteRenderer::getFlipX() const {
	return _flipX;
}

const bool SpriteRenderer::getFlipY() const {
	return _flipY;
}

void SpriteRenderer::setFlipX(const bool value) {
	_flipX = value;
}

void SpriteRenderer::setFlipY(const bool value) {
	_flipY = value;
}

void SpriteRenderer::draw(char* buffer, unsigned int* depthBuffer) {
	if (_sprite == nullptr || _transform == nullptr) { return; }

	const auto mat = _transform->getMatrix(true);

	const auto sprtB = _sprite->getBounds(_flipX, _flipY);
	const auto sprtCenter = mat.multiplyPoint(sprtB.getCenter());
    auto sprtBS = mat.multiplyAbsVector(sprtB.getSize());

	sprtBS.set(abs(sprtBS.x), abs(sprtBS.y));

	_bounds.set(sprtCenter, sprtBS);
	Rect bounds(Rendering::GAME_AREA_BOUNDS);
	bounds.set(Rendering::MAIN_CAMERA->getPosition(true), Rendering::GAME_AREA_BOUNDS.getSize());

	if (!_bounds.overlaps(bounds)) { return; }

	if (DRAW_BOUNDS) {		
		_boundSprite = SpriteFactory::getBox(sprtBS.x, sprtBS.y);
		if (_boundSprite != nullptr) {
			unsigned int debugUN = _debugLayer.getUnion();
			_boundSprite->draw(sprtCenter, buffer, depthBuffer, debugUN, Rendering::CHAR_W, Rendering::GAME_AREA_H, Rendering::GAME_AREA_Y, _flipX, _flipY);
		}
	}

	unsigned int un = layer.getUnion();
	_sprite->draw(_transform, buffer, depthBuffer, un, Rendering::CHAR_W, Rendering::GAME_AREA_H, Rendering::GAME_AREA_Y, _flipX, _flipY);
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

const Sprite* SpriteRenderer::getSprite() const {
	return _sprite;
}


