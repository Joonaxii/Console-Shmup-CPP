#pragma once
#include <vector>
#include "src/Engine/Math/Vector2.h"
#include "src/Engine/Math/Matrix3x3.h"

class Transform
{
public:

	Transform();
    ~Transform();

	const Matrix3x3 getMatrix(const bool isWorld) const;

	const Vector2 getPosition(const bool isWorld) const;
	const float getRotation(const bool isWorld) const;
	const Vector2 getScale(const bool isWorld) const;

	void setPosition(const Vector2& position, const bool isWorld);
	void setRotation(const float position, const bool isWorld);
	void setScale(const Vector2& scale, const bool isWorld);

	void setParent(Transform* parent);
	const Transform* getParent() const;

	void addChild(Transform* tr);
	void removeChild(Transform* tr);

private:

	Transform* _parent;

	Matrix3x3 _localMatrix;
	Matrix3x3 _worldMatrix;

	Vector2 _localPosition;
	Vector2 _worldPosition;

	float _localRotation;
	float _worldRotation;

	Vector2 _localScale;
	Vector2 _worldScale;

	std::vector<Transform*> _children;

	void notifyChildren();
	void updateWorld(const bool setLocalToWorld);
};

