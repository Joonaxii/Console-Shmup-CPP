#include "Transform.h"
#include <algorithm>
#include "../Math/Matrix3x3.h"

Transform::Transform() : _children(0), _localMatrix(), _worldMatrix(), 
_localPosition(0, 0), _localRotation(0), _localScale(1, 1),
_worldPosition(0, 0), _worldRotation(0), _worldScale(1, 1),
_parent(nullptr)
{
	setPosition(_localPosition, false);
	setRotation(_localRotation, false);
	setScale(_localScale, false);
}

Transform::~Transform()
{
}

const Matrix3x3 Transform::getMatrix(const bool isWorld) const {
	return Matrix3x3(isWorld ? _worldMatrix : _localMatrix);
}

const Vector2 Transform::getPosition(const bool isWorld) const {
	return isWorld ? Vector2(_worldPosition) : Vector2(_localPosition);
}

const float Transform::getRotation(const bool isWorld) const {
	return isWorld ? _worldRotation : _localRotation;
}

const Vector2 Transform::getScale(const bool isWorld) const {
	return isWorld ? Vector2(_worldScale) : Vector2(_localScale);
}

void Transform::setPosition(const Vector2& position, const bool isWorld) {
	if (isWorld) {

		_worldPosition.set(position);

		_worldMatrix.setPosition(_worldPosition);
		_localMatrix.setPosition(_localPosition = _parent != nullptr ? _worldMatrix.inversePosition() : _worldPosition);

		notifyChildren();
		return;
	}

	_localPosition.set(position);

	_localMatrix.setPosition(_localPosition);
	_worldMatrix.setPosition(_worldPosition = _parent != nullptr ? _parent->_worldMatrix.multiplyPoint(_localPosition) : _localPosition);
	notifyChildren();
}

void Transform::setRotation(const float rotation, const bool isWorld) {
	if (isWorld) {

		_worldRotation = rotation;

		_worldMatrix.setRotation(_worldRotation);
		_localMatrix.setRotation(_localRotation = _parent != nullptr ? _worldMatrix.inverseRotation() : _worldRotation);

		notifyChildren();
		return;
	}

	_localRotation = rotation;

	_localMatrix.setRotation(_localRotation);
	_worldMatrix.setRotation(_worldRotation = _parent != nullptr ? _parent->_worldMatrix.rotate(_localRotation) : _localRotation);
	notifyChildren();
}

void Transform::setScale(const Vector2& scale, const bool isWorld) {
	if (isWorld) {

		_worldScale.set(scale);

		_worldMatrix.setScale(_worldScale);
		_localMatrix.setScale(_localScale = _parent != nullptr ? _worldMatrix.inverseScale() : _worldScale);

		notifyChildren();
		return;
	}

	_localScale.set(scale);

	_localMatrix.setScale(_localScale);
	_worldMatrix.setScale(_worldScale = _parent != nullptr ? _parent->_worldMatrix.scaleVector(_localScale) : _localScale);
	notifyChildren();
}

void Transform::setParent(Transform* parent) {

	auto prev = _parent;
	_parent = parent;

	if (prev != _parent) {
		if(prev != nullptr) {
			auto find = std::find(prev->_children.begin(), prev->_children.end(), this);
			if (find != prev->_children.end()) {
				prev->_children.erase(find);
			}

			if (_parent != nullptr) {
				_parent->_children.push_back(this);
			}
		}
	}
}

const Transform* Transform::getParent() const {
	return _parent;
}

void Transform::addChild(Transform* tr) {
	if (tr == nullptr || tr == this || _parent == tr) { return; }

	_children.push_back(tr);

	tr->updateWorld(true);
	tr->setParent(this);
}

void Transform::removeChild(Transform* tr) {
	if (tr == nullptr) { return; }

	auto find = std::find(_children.begin(), _children.end(), tr);
	if (find != _children.end()) {
		_children.erase(find);
	}

	tr->updateWorld(true);
	tr->setParent(nullptr);
}

void Transform::notifyChildren() {
	for (size_t i = 0; i < _children.size(); i++) {
		_children[i]->updateWorld(false);
	}
}

void Transform::updateWorld(const bool setLocalToWorld) {
	if (setLocalToWorld) {

		setPosition(_worldPosition, false);
		setRotation(_worldRotation, false);
		setScale(_worldScale, false);
	}

	if (_parent != nullptr) {
		_worldMatrix.setPosition(_worldPosition = _parent->_worldMatrix.multiplyPoint(_localPosition));
		_worldMatrix.setRotation(_worldRotation = _parent->_worldMatrix.rotate(_localRotation));
		_worldMatrix.setScale(_worldScale = _parent->_worldMatrix.scaleVector(_localScale));

		notifyChildren();
		return;
	}

	_worldMatrix.setPosition(_worldPosition = _localPosition);
	_worldMatrix.setRotation(_worldRotation = _localRotation);
	_worldMatrix.setScale(_worldScale = _localScale);

	notifyChildren();
}
