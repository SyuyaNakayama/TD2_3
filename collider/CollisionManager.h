#pragma once
#include <list>
#include "Collider.h"
#include <memory>
#include "player/Player.h"

class CollisionManager
{
private:
	bool CheckBoxCollisionPair(Collider* colliderA, Collider* colliderB);
public:
	void CheckAllCollisions(Player* player);
};