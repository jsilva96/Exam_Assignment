#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "CollisionManager.h"
#include "BaseCollisionHandler.h"
#include "Renderer.h"
ColliderComponent::ColliderComponent(const Rectf& rect)
	:m_Rect{ rect },
	m_IsStatic{ false },
	m_pHandler(nullptr)
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
	PoolManager::GetInstance().ReturnObject<ColliderComponent>(static_cast<BaseObject*>(ptrDelete));
}
ColliderComponent::~ColliderComponent()
{
	for (std::pair<const CollisionGroup, bool> & p : m_CollisionGroup) p.second = false;

	m_IsStatic = false;
	m_Rect = {};
	m_pPrevCurrentCollisions.clear();
	m_pCurrentCollisions.clear();
	m_pHandler = nullptr;

}
void ColliderComponent::Initialize()
{
	CollisionManager::GetInstance().AddCollider(this);
	if (!m_pHandler)
	{
		throw std::exception("ColliderComponent::No ColliderHandler Found");
	}
}
void ColliderComponent::Update()
{
	m_Rect.leftBottom = GetGameObject()->GetTransform()->GetPosition();

	m_pPrevCurrentCollisions.clear();
	m_pPrevCurrentCollisions.assign(m_pCurrentCollisions.begin(), m_pCurrentCollisions.end());

	m_pCurrentCollisions.clear();
}
void ColliderComponent::Render() const
{
//	Color4f c{ 0.0f, 0.0f, 0.0f, 0.5f };

//	dae::Renderer::GetInstance().RenderRect(m_Rect, c);
}
void ColliderComponent::SetCollisionGroup(CollisionGroup group, bool b)
{
	m_CollisionGroup[group] = b;
}

void ColliderComponent::HandleCollision(ColliderComponent* pComp, bool isColliding)
{
	const auto it = std::find(m_pPrevCurrentCollisions.begin(), m_pPrevCurrentCollisions.end(), pComp);

	if (!isColliding && it != m_pPrevCurrentCollisions.end())
	{	
		m_pHandler->OnCollideExit(pComp);
		m_pPrevCurrentCollisions.erase(it);
		return;
	}
	if(isColliding)
	{ 
		if (it != m_pPrevCurrentCollisions.end()) m_pHandler->OnCollideStay(pComp);
		else m_pHandler->OnCollideEnter(pComp);
		m_pCurrentCollisions.push_back(pComp);
	}
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

void ColliderComponent::AddHandler(BaseCollisionHandler* pHandler)
{
	m_pHandler = pHandler;
}
