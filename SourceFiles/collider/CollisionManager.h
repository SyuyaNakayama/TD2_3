#pragma once
#include "Collider.h"
#include <list>
#include <Collision.cpp>

class CollisionManager final
{
private:
	static std::list<BoxCollider*> boxColliders;
	static std::list<SphereCollider*> sphereColliders;
	static std::list<PlaneCollider*> planeColliders;
	static std::list<PolygonCollider*> triangleColliders;
	static std::list<RayCollider*> rayColliders;

	static bool CheckCollisionFiltering(BaseCollider* colliderA, BaseCollider* colliderB);
	static bool CheckCollision2Boxes(BoxCollider* colliderA, BoxCollider* colliderB);
	static bool CheckCollision2Spheres(SphereCollider* colliderA, SphereCollider* colliderB);
	//static bool CheckCollisionSpherePlane(const Sphere& sphere, const Plane& plane, Vector3* inter = nullptr);
	//static bool CheckCollisionSphereTriangle(const Sphere& sphere, const Triangle& triangle, Vector3* inter = nullptr);
	static bool CheckCollisionRayPlane(RayCollider* colliderA, PlaneCollider* colliderB, float* distance = nullptr, bool isPolygonCollideCheck = false);
	static bool CheckCollisionRayPolygon(RayCollider* colliderA, PolygonCollider* colliderB, float* distance = nullptr);
	//static bool CheckCollisionRaySphere(const Ray& ray, const Sphere& sphere, float* distance = nullptr, Vector3* inter = nullptr);

public:
	CollisionManager() = delete;
	// コライダー登録関数
	static void PushCollider(BoxCollider* collider) { boxColliders.push_back(collider); }
	static void PushCollider(SphereCollider* collider) { sphereColliders.push_back(collider); }
	static void PushCollider(PlaneCollider* collider) { planeColliders.push_back(collider); }
	static void PushCollider(PolygonCollider* collider) { triangleColliders.push_back(collider); }
	static void PushCollider(RayCollider* collider) { rayColliders.push_back(collider); }
	static void PopCollider(BoxCollider* collider) { boxColliders.remove(collider); }
	static void PopCollider(SphereCollider* collider) { sphereColliders.remove(collider); }
	static void PopCollider(PlaneCollider* collider) { planeColliders.remove(collider); }
	static void PopCollider(PolygonCollider* collider) { triangleColliders.remove(collider); }
	static void PopCollider(RayCollider* collider) { rayColliders.remove(collider); }
	// 個別当たり判定
	static void CheckBoxCollisions();
	static void CheckSphereCollisions();
	static void CheckRayPlaneCollisions();
	static void CheckRayPolygonCollisions();
	// 全当たり判定
	static void CheckAllCollisions();
};