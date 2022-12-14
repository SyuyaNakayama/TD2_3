#pragma once
#include "WorldTransform.h"

enum class CollisionAttribute
{
	Player = 0b1,
	Block = 0b1 << 1,
	All = -1
};

enum class CollisionMask
{
	Player = ~(int)CollisionAttribute::Player,
	Block = ~(int)CollisionAttribute::Block,
	All = -1
};

class Collider
{
private:
	CollisionAttribute collisionAttribute_ = CollisionAttribute::All;
	CollisionMask collisionMask_ = CollisionMask::All;

protected:
	WorldTransform worldTransform;

public:
	Collider();
	~Collider();

	virtual void OnCollision(Collider* collider) {};
	virtual Vector3 GetWorldPosition() { return worldTransform.GetWorldPosition(); };
	virtual Vector3 GetRadius() { return worldTransform.scale_; };

	CollisionAttribute GetCollisionAttribute() { return collisionAttribute_; }
	CollisionMask GetCollisionMask() { return collisionMask_; }
	void SetCollisionAttribute(CollisionAttribute collisionAttribute) { collisionAttribute_ = collisionAttribute; }
	void SetCollisionMask(CollisionMask collisionMask) { collisionMask_ = collisionMask; }
};