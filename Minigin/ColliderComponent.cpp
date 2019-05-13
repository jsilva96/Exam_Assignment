#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "CollisionManager.h"
#include "Renderer.h"
ColliderComponent::ColliderComponent(const Rectf& rect)
	:m_Rect{ rect },
	m_IsStatic{ false }
{
	m_CollisionGroup[static_cast<CollisionGroup>(0)] = true;
	for (int i = 1; i < 10; i++) m_CollisionGroup[static_cast<CollisionGroup>(i)] = false;
}
ColliderComponent::ColliderComponent()
	:ColliderComponent(Rectf{})
{
}

void* ColliderComponent::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<ColliderComponent>();
}
void ColliderComponent::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject(static_cast<BaseObject*>(ptrDelete));
}
ColliderComponent::~ColliderComponent()
{
	for (std::pair<const CollisionGroup, bool> & p : m_CollisionGroup) p.second = false;

	m_IsStatic = false;
	m_Rect = {};
}
void ColliderComponent::Initialize()
{
	CollisionManager::GetInstance().AddCollider(this);
}
void ColliderComponent::Update()
{
	m_Rect.leftBottom = GetGameObject()->GetTransform()->GetPosition();
}
void ColliderComponent::Render() const
{
	//	Color4f c{ 1.0f, 1.0f, 1.0f, 0.1f };

//	dae::Renderer::GetInstance().RenderRect(m_Rect, c);
}
void ColliderComponent::SetCollisionGroup(CollisionGroup group, bool b)
{
	m_CollisionGroup[group] = b;
}
Rectf ColliderComponent::GetRectf() const
{
	return m_Rect;
}
std::vector<CollisionGroup> ColliderComponent::GetCollisionGroups() const
{
	std::vector<CollisionGroup> obj;
	if (!IsUsable()) return obj;

	for (const std::pair<CollisionGroup, bool>& pC : m_CollisionGroup) if (pC.second) obj.push_back(pC.first);

	return obj;
}