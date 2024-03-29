#include "Collider.h"
#include "CollisionManager.h"
#include "Quaternion.h"
#include <array>

float IncludeCollider::includeRadius = 0.1f;

BoxCollider::BoxCollider() { CollisionManager::PushCollider(this); }
BoxCollider::~BoxCollider() { CollisionManager::PopCollider(this); }
SphereCollider::SphereCollider() { CollisionManager::PushCollider(this); }
SphereCollider::~SphereCollider() { CollisionManager::PopCollider(this); }
RayCollider::RayCollider() { CollisionManager::PushCollider(this); }
RayCollider::~RayCollider() { CollisionManager::PopCollider(this); }
PolygonCollider::PolygonCollider() { CollisionManager::PushCollider(this); }
PolygonCollider::~PolygonCollider() { CollisionManager::PopCollider(this); }
PlaneCollider::PlaneCollider() { CollisionManager::PushCollider(this); }
PlaneCollider::~PlaneCollider() { CollisionManager::PopCollider(this); }
IncludeCollider::IncludeCollider() { CollisionManager::PushCollider(this); }
IncludeCollider::~IncludeCollider() { CollisionManager::PopCollider(this); }

void PolygonCollider::SetVertices()
{
	Vector3 objPos = worldTransform.translation_;
	Vector3 objRad = worldTransform.scale_;
	Quaternion rotQ = DirectionToDirection({ 0,0,-1 }, normal.normalize());
	std::array<Vector3, 4> verticesTemp =
	{ {
		{-objRad.x, objRad.y, -objRad.z},
		{objRad.x, objRad.y, -objRad.z},
		{objRad.x, -objRad.y, -objRad.z},
		-objRad
	} };

	vertices.clear();
	for (auto& vertex : verticesTemp) 
	{
		vertices.push_back(objPos+ RotateVector(vertex, rotQ));
	}

	//vertices.push_back(objPos + Vector3(-objRad.x, objRad.y, -objRad.z));
	//vertices.push_back(objPos + Vector3(objRad.x, objRad.y, -objRad.z));
	//vertices.push_back(objPos + Vector3(objRad.x, -objRad.y, -objRad.z));
	//vertices.push_back(objPos - objRad);
}

void PolygonCollider::ToPlaneCollider(PlaneCollider* planeCollider)
{
	planeCollider->SetDistance(distance);
	planeCollider->SetNormal(normal);
}