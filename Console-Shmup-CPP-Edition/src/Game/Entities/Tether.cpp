#include "Tether.h"
#include "../../Engine/Math/Math.h"

Tether::Tether() : Tether(4, 1.0f, 1.0f, 1.0f, 1.0f, WaveSpecifications(), 1.0f, 5.0f) { }

Tether::Tether(const int tetherSize, const float speedGlobal, const float speedSeg, const float startSize, const float endSize, const WaveSpecifications& wave, const float bendPower, const float bendPowerMaxDist) : _tetherSize(tetherSize), _globalTimeSpeed(speedGlobal), _segTimeSpeed(speedSeg), _wave(wave), _bendPower(bendPower), _bendDist(bendPowerMaxDist) {
	_tetherObjs = new GenericEntity*[tetherSize];

	const float l = _tetherSize < 2.0f ? 1.0f : _tetherSize - 1.0f;
	for (size_t i = 0; i < tetherSize; i++) {
		auto teth = _tetherObjs[i] = new GenericEntity("Tether", nullptr, false, "Default", false, 0);
		const float scal = lerp(startSize, endSize, i / l);
		teth->getTransform()->setScale(Vector2(scal, scal), false);
	}
}

Tether::~Tether() {
	delete[] _tetherObjs;
}

void Tether::setSprite(Sprite* sprite, const std::string layer, const short startOrder) {
	for (size_t i = 0; i < _tetherSize; i++) {
		auto rend = _tetherObjs[i]->getRenderer();
		rend->setSprite(sprite);
		rend->setLayer(layer);
		rend->setSortingOrder(startOrder - i);
	}
}

void Tether::setPoint(Transform* tr, const Vector2& offset, const bool isA) {
	if (isA) {
		_pointA = tr;
		_offsetA = offset;
		return;
	}

	_pointB = tr;
	_offsetB = offset;
}

void Tether::update(const float delta) {
	if (_pointA == nullptr || _pointB == nullptr) { return; }

	const float l = _tetherSize < 2.0f ? 1.0f : _tetherSize - 1.0f;

	const Vector2 startPoint(_pointA->getPosition(true) + _offsetA);
	const Vector2 endPoint(_pointB->getPosition(true) + _offsetB);

	const Vector2 head = (endPoint - startPoint).getNormalized();

	const bool isLeft = startPoint.x < endPoint.x;
	const float dist = abs(endPoint.x - startPoint.x);
	const float bendPower = clamp(dist / _bendDist, 0.0f, 1.0f);

	_timeGlobal += delta *_globalTimeSpeed;
	_timeSeg += delta * _segTimeSpeed;

	const Vector2 midPoint(Vector2::lerp(startPoint, endPoint, 0.5f) + Vector2::rotate(head, isLeft ? -90.0f : 90.0f) * _bendPower);

	const float h = _tetherSize * 0.5f;
	const float hL = h < 2.0f ? 1.0f : h - 1.0f;
	for (size_t i = 0; i < _tetherSize; i++) {
		const float n = i / l;
		const float n2 = i <= h ? i / hL : 1.0f - ((i - h) / hL);
		auto tr = _tetherObjs[i]->getTransform();

		const Vector2 bezPoint(quadraticBezierCurve(startPoint, midPoint, endPoint, n));
		const Vector2 linearPoint(Vector2::lerp(startPoint, endPoint, n));
		const Vector2 sinePoint(_wave.getValue(_timeGlobal, (_timeSeg + (n * 180.0f)) * DEG_2_RAD), 0.0f);

		const Vector2 pos(Vector2::lerp(linearPoint, bezPoint, bendPower * n2) + Vector2::lerp(Vector2::zero, sinePoint, (1.0f - bendPower * 0.5f) * n2));
		tr->setPosition(pos, true);
	}
}
