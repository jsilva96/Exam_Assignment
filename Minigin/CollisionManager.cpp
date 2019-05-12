#pragma once
#include "MiniginPCH.h"
#include "CollisionManager.h"
#include "LevelColliderComponent.h"
#include <algorithm>

bool operator<(const Quadrant& q1, const Quadrant& q2)
{
	if (q1.leftBottom.x == q2.leftBottom.x) return q1.leftBottom.y < q2.leftBottom.y;
	else return q1.leftBottom.x < q2.leftBottom.x;
}

CollisionManager* CollisionManager::m_pInstance = nullptr;
CollisionManager::CollisionManager()
	:m_WindowDims{}
{
}
CollisionManager::~CollisionManager()
{
}

CollisionManager& CollisionManager::GetInstance()
{
	if (!m_pInstance) m_pInstance = new CollisionManager();
	return *m_pInstance;
}

void CollisionManager::DestroyInstance()
{
	delete m_pInstance;
}
void CollisionManager::Update()
{
	UpdateDynamicQuadrants();

	for (std::pair<const Quadrant, std::vector<ColliderComponent*>>& p : m_pStaticColliders) CheckQuadrantCollisions(p.second);
	for (std::pair<const Quadrant, std::vector<ColliderComponent*>>& p : m_pDynamicColliders) CheckQuadrantCollisions(p.second);

	for (std::pair<const Quadrant, std::vector<ColliderComponent*>>& p : m_pDynamicColliders)
	{
		for (ColliderComponent* pC : p.second)
		{
			for (ColliderComponent* pC2 : m_pStaticColliders[p.first])
			{
				if (CanCollide(pC->GetCollisionGroups(), pC2->GetCollisionGroups()))
				{
					if (CheckForCollision(pC2, pC))
					{
						pC2->HandleCollision(pC);
						pC->HandleCollision(pC2);
					}
				}
			}
		}
	}

	if (!m_pLevel) return;
	for (std::pair<const Quadrant, std::vector<ColliderComponent*>>& p : m_pDynamicColliders)
	{
		for (ColliderComponent* pC : p.second)CheckLevelCollision(pC);
	}
}
void CollisionManager::UpdateDynamicQuadrants()
{
	for (std::pair<const Quadrant, std::vector<ColliderComponent*>>& p : m_pDynamicColliders)p.second.clear();
	for (std::pair<const Quadrant, std::vector<ColliderComponent*>>& p : m_pStaticColliders)p.second.clear();

	for (ColliderComponent* pC : m_pColliders) AddCollider(pC);
}
void CollisionManager::CheckQuadrantCollisions(std::vector<ColliderComponent*>& colliders)
{
	if (colliders.size() <= 1) return;
	auto lambda = [&](ColliderComponent* pC1)
	{
		if (*(colliders.end() - 1) == pC1) return;
		bool b = false;
		
		for (ColliderComponent* pC : colliders)
		{
			if (!b) b = !b && (pC == pC1);
			else
			{
				if (CanCollide(pC1->GetCollisionGroups(), pC->GetCollisionGroups()))
				{
					if (CheckForCollision(pC1, pC))
					{
						pC->HandleCollision(pC1);
						pC1->HandleCollision(pC);
					}
				}
			}
		}
	};
	std::for_each(colliders.begin(), colliders.end(), lambda);
}
void CollisionManager::CreateQuadrants()
{
	int nrOfQuadrants{ 512 };

	int root{ int(sqrt(nrOfQuadrants)) };

	int horizontalQuads{};
	int verticalQuads{};
	bool isPrime{};

	if (pow(root, 2) == nrOfQuadrants)
	{
		horizontalQuads = root;
		verticalQuads = root;
	}
	else
	{
		std::vector<int> div;

		if (!IsPrime(nrOfQuadrants) || nrOfQuadrants == 2)GetDivisibles(div, nrOfQuadrants);
		else
		{
			GetDivisibles(div, (nrOfQuadrants - 1));
			isPrime = true;
		}
		int halfSize = int(div.size()) / 2;

		horizontalQuads = div[halfSize];
		verticalQuads = div[--halfSize];
	}

	Quadrant quad{};
	quad.height = float(m_WindowDims.height / verticalQuads);
	quad.width = float(m_WindowDims.width / horizontalQuads);


	for (int i = 0; i < horizontalQuads; i++)
	{
		if (i == (horizontalQuads - 1) && isPrime)
		{
			int n = nrOfQuadrants - ((verticalQuads - 1) * horizontalQuads);
			quad.height = float(m_WindowDims.height / --n);
			++verticalQuads;
		}
		for (int j = 0; j < verticalQuads; j++)
		{
			m_pStaticColliders[quad];
			m_pDynamicColliders[quad];
			quad.leftBottom.y += quad.height;
		}
		quad.leftBottom.x += quad.width;
		quad.leftBottom.y = 0.0f;
	}
}
void CollisionManager::AddCollider(ColliderComponent * pCollider)
{
	if (!pCollider->IsUsable()) return;
	
	if (!pCollider->IsStatic()) LoadColliderToQuadrants(pCollider, m_pDynamicColliders);
	else LoadColliderToQuadrants(pCollider, m_pStaticColliders);

	AddCheck(m_pColliders, pCollider);
}
void CollisionManager::LoadColliderToQuadrants(ColliderComponent* pCollider, std::map<Quadrant, std::vector<ColliderComponent*>>& container)
{
	for (std::pair<const Quadrant, std::vector<ColliderComponent*>>& p : container)
	{
		if (IsInQuadrant(p.first, pCollider))AddCheck(p.second, pCollider);
	}
}
void CollisionManager::AddLevelCollider(LevelColliderComponent * pCollider)
{
	m_pLevel = pCollider;
}
bool CollisionManager::CheckForCollision(ColliderComponent * pC1, ColliderComponent * pC2)
{
	Rectf r1{ pC1->GetRectf() };
	Rectf r2{ pC2->GetRectf() };

	r1.leftBottom.y -= r1.height;
	r2.leftBottom.y -= r2.height;

	if ((r1.leftBottom.x + r1.width) < r2.leftBottom.x || (r2.leftBottom.x + r2.width) < r1.leftBottom.x) return false;	
	if (r1.leftBottom.y > (r2.leftBottom.y + r2.height) || r2.leftBottom.y > (r1.leftBottom.y + r1.height)) return false;
	
	return true;
}
bool CollisionManager::IsInQuadrant(const Quadrant & q, ColliderComponent* pC)
{
	Rectf r1{ pC->GetRectf() };
	Rectf r2{ q };

	r1.leftBottom.y -= r1.height;

	if ((r1.leftBottom.x + r1.width) < r2.leftBottom.x || (r2.leftBottom.x + r2.width) < r1.leftBottom.x) return false;
	if (r1.leftBottom.y > (r2.leftBottom.y + r2.height) || r2.leftBottom.y > (r1.leftBottom.y + r1.height)) return false;

	return true;
}
bool CollisionManager::CanCollide(const std::vector<CollisionGroup>& collisions1, const std::vector<CollisionGroup>& collisions2)
{
	if (collisions1.empty() || collisions2.empty()) return false;
	for (const CollisionGroup& cg1 : collisions1)
	{
		for (const CollisionGroup& cg2 : collisions2) if (cg1 == cg2) return true;
	}

	return false;
}
void CollisionManager::CheckLevelCollision(ColliderComponent* pC1)
{
	Rectf playerRect{pC1->GetRectf() };

	playerRect.leftBottom.y -= playerRect.height;
	Point2f p1{ playerRect.leftBottom.x, playerRect.leftBottom.y + (playerRect.height / 2) };
	Point2f p2{ p1.x + playerRect.width, p1.y };
	HitInfo info;

	for (const std::vector<Point2f>& verts : m_pLevel->GetVerts())
	{
		if (Raycast(verts, p1, p2, info))
		{
			m_pLevel->OnLevelCollide(info, pC1);
			return;
		}
	}

	p1 = { playerRect.leftBottom.x + (playerRect.width / 2), playerRect.leftBottom.y };
	p2 = { p1.x, p1.y + playerRect.height };

	for (const std::vector<Point2f>& verts : m_pLevel->GetVerts())
	{
		if (Raycast(verts, p1, p2, info))
		{
			m_pLevel->OnLevelCollide(info, pC1);
			return;
		}
	}
}