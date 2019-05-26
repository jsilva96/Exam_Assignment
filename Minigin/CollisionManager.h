#pragma once
#include "ColliderComponent.h"

class LevelColliderComponent;

struct Window
{
	int width, height;

	Window(int width, int height)
		:width{ width },
		height{ height }
	{
	}
	Window()
		:Window(0, 0)
	{
	}
};
struct Quadrant : public Rectf
{
};
class CollisionManager
{
public:
	static CollisionManager& GetInstance();
	void DestroyInstance();

	~CollisionManager();

	void Update();
	void AddCollider(ColliderComponent* pCollider, bool loadToColliders = true);
	void AddLevelCollider(LevelColliderComponent* pCollider);

	void LoadWindow(int width, int height)
	{
		m_WindowDims.height = height;
		m_WindowDims.width = width;

		CreateQuadrants();
	}

	void CreateQuadrants();

private:
	static CollisionManager * m_pInstance;
	std::vector<ColliderComponent*> m_pColliders;

	std::map<Quadrant, std::vector<ColliderComponent*>> m_pStaticColliders;
	std::map<Quadrant, std::vector<ColliderComponent*>> m_pDynamicColliders;

	LevelColliderComponent* m_pLevel;

	Window m_WindowDims;
	CollisionManager();

	void CheckQuadrantCollisions(std::vector<ColliderComponent*>& colliders);

	void UpdateDynamicQuadrants();

	bool CheckForCollision(ColliderComponent* pC1, ColliderComponent* pC2);
	bool IsInQuadrant(const Quadrant& q, ColliderComponent* pC);
	inline bool CanCollide(const std::vector<CollisionGroup>& collisions1, const std::vector<CollisionGroup>& collisions2);

	void CheckLevelCollision(ColliderComponent* pC1);

	void LoadColliderToQuadrants(ColliderComponent* pCollider, std::map<Quadrant, std::vector<ColliderComponent*>>& container);

	bool IsOverlapping(const Rectf & r1, const Rectf & r2)
	{
		if ((r1.leftBottom.x + r1.width) < r2.leftBottom.x || (r2.leftBottom.x + r2.width) < r1.leftBottom.x) return false;

		if (r1.leftBottom.y > (r2.leftBottom.y + r2.height) || r2.leftBottom.y > (r1.leftBottom.y + r1.height)) return false;

		return true;
	}
	bool IsPointOnLineSegment(const Point2f& p, const Point2f& a, const Point2f& b)
	{
		Vector2f ap{ a, p }, bp{ b, p };
		// If not on same line, return false
		if (abs(ap.CrossProduct(bp)) > 0.001f) return false;

		// Both vectors must point in opposite directions if p is between p1 and p2
		if (ap.Dot(bp) > 0) return false;

		return true;
	}

	bool IntersectLineSegments(const Point2f& p1, const Point2f& p2, const Point2f& q1, const Point2f& q2, float& outLambda1, float& outLambda2, float epsilon = 1e-6)
	{
		bool intersecting{ false };

		Vector2f p1p2{ p1, p2 };
		Vector2f q1q2{ q1, q2 };

		// cross product to determine if parallel
		float denom = p1p2.CrossProduct(q1q2);

		// Don't divide by zero
		if (std::abs(denom) > epsilon)
		{
			intersecting = true;

			Vector2f p1q1{ p1, q1 };

			float num1 = p1q1.CrossProduct(q1q2);
			float num2 = p1q1.CrossProduct(p1p2);
			outLambda1 = num1 / denom;
			outLambda2 = num2 / denom;
		}
		else // are parallel
		{
			//connect start points
			Vector2f p1q1{ p1, q1 };

			// cross product to determine if segments and the line connecting their start points are parallel, 
			// if so, than they are on a line
			// if not, then there is no intersection

			if (std::abs(p1q1.CrossProduct(q1q2)) > epsilon) return false;

			// check the 4 conditions
			outLambda1 = 0;
			outLambda2 = 0;
			if (IsPointOnLineSegment(p1, q1, q2))intersecting = true;
			if (IsPointOnLineSegment(p2, q1, q2))intersecting = true;
			if (IsPointOnLineSegment(q1, p1, p2))intersecting = true;
			if (IsPointOnLineSegment(q2, p1, p2))intersecting = true;
		}
		return intersecting;
	}
	bool Raycast(const Point2f* vertices, const size_t nrVertices, const Point2f& rayP1, const Point2f& rayP2, HitInfo& hitInfo)
	{
		if (nrVertices == 0)
		{
			return false;
		}

		std::vector<HitInfo> hits;

		Rectf r1, r2;
		// r1: minimal AABB rect enclosing the ray
		r1.leftBottom.x = (std::min)(rayP1.x, rayP2.x);
		r1.leftBottom.y = (std::min)(rayP1.y, rayP2.y);
		r1.width = (std::max)(rayP1.x, rayP2.x) - r1.leftBottom.x;
		r1.height = (std::max)(rayP1.y, rayP2.y) - r1.leftBottom.y;

		// Line-line intersections.
		for (size_t idx{ 0 }; idx <= nrVertices; ++idx)
		{
			// Consider line segment between 2 consecutive vertices
			// (modulo to allow closed polygon, last - first vertice)
			Point2f q1 = vertices[(idx + 0) % nrVertices];
			Point2f q2 = vertices[(idx + 1) % nrVertices];

			// r2: minimal AABB rect enclosing the 2 vertices
			r2.leftBottom.x = (std::min)(q1.x, q2.x);
			r2.leftBottom.y = (std::min)(q1.y, q2.y);
			r2.width = (std::max)(q1.x, q2.x) - r2.leftBottom.x;
			r2.height = (std::max)(q1.y, q2.y) - r2.leftBottom.y;

			if (IsOverlapping(r1, r2))
			{
				float lambda1{};
				float lambda2{};
				if (IntersectLineSegments(rayP1, rayP2, q1, q2, lambda1, lambda2))
				{
					if (lambda1 > 0 && lambda1 <= 1 && lambda2 > 0 && lambda2 <= 1)
					{
						HitInfo hitObj;
						hitObj.lambda = lambda1;
						hitObj.intersectPoint = { rayP1.x + ((rayP2.x - rayP1.x) * lambda1), rayP1.y + ((rayP2.y - rayP1.y) * lambda1) };
						hitObj.normal = Vector2f{ q2 - q1 }.Orthogonal().Normalize();
						hits.push_back(hitObj);
					}
				}
			}
		}

		if (hits.size() == 0)
		{
			return false;
		}

		// Get closest intersection point and copy it into the hitInfo parameter
		hitInfo = *std::min_element(hits.begin(), hits.end(),
			[](const HitInfo& first, const HitInfo& last) {
			return first.lambda < last.lambda; });
		return true;
	}
	bool Raycast(const std::vector<Point2f>& vertices, const Point2f& rayP1, const Point2f& rayP2, HitInfo& hitInfo)
	{
		return Raycast(vertices.data(), vertices.size(), rayP1, rayP2, hitInfo);
	}
};