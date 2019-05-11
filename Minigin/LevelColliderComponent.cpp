#include "MiniginPCH.h"
#include "LevelColliderComponent.h"

#include "CollisionManager.h"

LevelColliderComponent::LevelColliderComponent()
	:ColliderComponent()
{
}
LevelColliderComponent::~LevelColliderComponent()
{
}
void LevelColliderComponent::Initialize()
{
	CollisionManager::GetInstance().AddLevelCollider(this);
}
void LevelColliderComponent::Update()
{
}
void LevelColliderComponent::Render() const
{
}
void LevelColliderComponent::Reset()
{
	ColliderComponent::Reset();

	for (std::vector<Point2f>& p : m_Verts) p.clear();
	
	m_Verts.clear();
}
void LevelColliderComponent::AddVerts(const std::vector<Point2f>& verts)
{
	AddCheck(m_Verts, verts);
}
const std::vector<std::vector<Point2f>>& LevelColliderComponent::GetVerts() const
{
	return m_Verts;
}
